
#include "main.h"
#include "manager.h"
#include "audioManager.h"
#include "fade.h"
#include "audio.h"
#include "player.h"
#include "box.h"
#include <fstream>
#include <thread>



IXAudio2* Audio::m_Xaudio{};
IXAudio2MasteringVoice* Audio::m_MasteringVoice{};
X3DAUDIO_HANDLE	 Audio::m_X3DaudioHandle{};

void Audio::InitMaster()
{

	// COM初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	
	MFStartup(MF_VERSION);
	// XAudio生成
	XAudio2Create(&m_Xaudio, 0);

	// マスタリングボイス生成
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
	
	X3DAudioInitialize(SPEAKER_STEREO, SPEED_OF_SOUND,m_X3DaudioHandle);
}


void Audio::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	MFShutdown();
	CoUninitialize();
}


void Audio::LoadSoundFile(const wchar_t* filename)
{
	WAVEFORMATEX* wfx = { 0 };
	{
		// Media Foundation オブジェクトの作成
		MFCreateSourceReaderFromURL(filename, nullptr, &m_SourceReader);
		assert(m_SourceReader);

		// 出力形式の取得
		IMFMediaType* pAudioType = nullptr;
		MFCreateMediaType(&pAudioType);
		pAudioType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		pAudioType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		m_SourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, pAudioType);

		//フォーマットの取得
		m_SourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &m_NativeType);

		UINT32 size;
		MFCreateWaveFormatExFromMFMediaType(m_NativeType, &wfx, &size);

		m_Xaudio->CreateSourceVoice(&m_Data.SourceVoice, wfx);

		m_Data.SourceVoice->Start();
	}
}

void Audio::Load(const wchar_t* filename)
{
	if (AudioManager::GetInstance()->GetSameName(m_Data.Name))
		return;


	WAVEFORMATEX* wfx = { 0 };
	{
		// Media Foundation オブジェクトの作成
		IMFSourceReader* pSourceReader = nullptr;
		MFCreateSourceReaderFromURL(filename, nullptr, &pSourceReader);

		assert(pSourceReader);

		// 出力形式の取得
		IMFMediaType* pAudioType = nullptr;
		MFCreateMediaType(&pAudioType);
		pAudioType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		pAudioType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		pSourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, pAudioType);

		//フォーマットの取得
		IMFMediaType * pNativeType = nullptr;
		pSourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &pNativeType);

		UINT32 size;
		MFCreateWaveFormatExFromMFMediaType(pNativeType, &wfx, &size);

		// 音声データの読み込みと再生
		IMFSample* pSample = nullptr;
		IMFMediaBuffer* pBuffer = nullptr;
		BYTE* pAudioData = nullptr;
		DWORD audioDataLength = 0;
		DWORD streamIndex, flags;
		LONGLONG llTimeStamp;

		while (true) {
			
			pSourceReader->ReadSample(
				MF_SOURCE_READER_FIRST_AUDIO_STREAM,
				0,
				&streamIndex,
				&flags,
				&llTimeStamp,
				&pSample
			);

			if (flags & MF_SOURCE_READERF_ENDOFSTREAM) {
				break;
			}

			if (pSample) {
				pSample->ConvertToContiguousBuffer(&pBuffer);

				pBuffer->Lock(&pAudioData, nullptr, &audioDataLength);
				m_Data.AudioData.insert(m_Data.AudioData.end(), pAudioData, pAudioData + audioDataLength);
				pBuffer->Unlock();

				pSample->Release();
				pBuffer->Release();
			}
		}

		pSourceReader->Release();
		pAudioType->Release();
		pNativeType->Release();
	}

	m_Data.Length = m_Data.AudioData.size();
	m_Data.PlayLength = m_Data.AudioData.size() / wfx->nBlockAlign;

	m_Xaudio->CreateSourceVoice(&m_Data.SourceVoice, wfx);

}



void Audio::Init(AudioMode audioMode)
{
	m_AudioMode = audioMode;
	m_DspSettings.SrcChannelCount = 2;
	m_DspSettings.DstChannelCount = 2;
	m_DspSettings.pMatrixCoefficients = new FLOAT32[m_DspSettings.SrcChannelCount * m_DspSettings.DstChannelCount];
	m_DspSettings.pDelayTimes = nullptr;
}

void Audio::Uninit()
{

	m_Data.SourceVoice->Stop();
	delete m_DspSettings.pMatrixCoefficients;
	
	if (m_Buffer != NULL)
	{
		m_Buffer->Unlock();
		m_Sample->Release();
		m_Buffer->Release();
		m_SourceReader->Release();
		m_NativeType->Release();
	}
}

void Audio::Update()
{
	m_Data.SourceVoice->GetState(&m_State);

	if (m_State.BuffersQueued == 0)
		m_IsSoundEnd = true;
	else
		m_IsSoundEnd = false;



	if (m_AudioMode == AUDIO_3D)
	{
		X3DAUDIO_CONE cone;
		cone.InnerAngle = X3DAUDIO_PI / 4.0f;  // 内側の角度（ラジアン）
		cone.OuterAngle = X3DAUDIO_PI / 2.0f;  // 外側の角度（ラジアン）
		cone.InnerVolume = 1.0f;  // 内側の音量（0.0 ～ 1.0）
		cone.OuterVolume = 0.5f;  // 外側の音量（0.0 ～ 1.0）
		cone.InnerLPF = 5000.0f;  // 内側のローパスフィルター周波数（Hz）
		cone.OuterLPF = 8000.0f;  // 外側のローパスフィルター周波数（Hz）

		//リスナー
		Player* player = Manager::GetInstance()->GetScene()->GetGameObject<Player>();
		if (player)
		{
			Transform* t = player->GetComponent<Transform>();
		

			m_Listener.OrientFront = t->GetForward();
			m_Listener.OrientTop = t->GetUp();
			m_Listener.Position = t->Position;
			m_Listener.Velocity = player->GetVelocity();

			m_Listener.pCone = &cone;

			//エミッター
			m_Emitter.ChannelCount = 2;
			m_Emitter.CurveDistanceScaler = 1.0f;
			m_Emitter.DopplerScaler = 1.0f;

			m_Emitter.pCone = &cone;

			FLOAT32 channelAzimuths[2] = { -90.0f, 90.0f };  // 左右耳の角度

			m_Emitter.pChannelAzimuths = channelAzimuths;

			X3DAUDIO_DISTANCE_CURVE volumeCurve;
			volumeCurve.PointCount = 7;  // ポイントの数

			X3DAUDIO_DISTANCE_CURVE_POINT points[7] = {
				{ 0.0f, 1.0f },    // リスナーからの距離が0メートルのときの音量
				{ 5.0f, 0.8f },    // リスナーからの距離が5メートルのときの音量
				{ 10.0f, 0.6f },   // リスナーからの距離が10メートルのときの音量
				{ 15.0f, 0.4f },   // リスナーからの距離が15メートルのときの音量
				{ 20.0f, 0.2f },   // リスナーからの距離が20メートルのときの音量
				{ 25.0f, 0.1f },   // リスナーからの距離が25メートルのときの音量
				{ 30.0f, 0.0f }	   // リスナーからの距離が30メートルのときの音量
			};

			volumeCurve.pPoints = points;

			m_Emitter.pVolumeCurve = &volumeCurve;

			X3DAUDIO_DISTANCE_CURVE lfeCurve;
			lfeCurve.PointCount = 4;  // ポイントの数

			X3DAUDIO_DISTANCE_CURVE_POINT lfePoints[4] = {
				{ 0.0f, 0.0f },    // リスナーからの距離が0メートルのときの低周波エフェクト
				{ 10.0f, 0.1f },   // リスナーからの距離が10メートルのときの低周波エフェクト
				{ 20.0f, 0.2f },   // リスナーからの距離が20メートルのときの低周波エフェクト
				{ 30.0f, 0.3f },   // リスナーからの距離が30メートルのときの低周波エフェクト
			};

			lfeCurve.pPoints = lfePoints;


			m_Emitter.pLFECurve = &lfeCurve;

			X3DAUDIO_DISTANCE_CURVE lpfDirectCurve;
			lpfDirectCurve.PointCount = 4;  // ポイントの数

			X3DAUDIO_DISTANCE_CURVE_POINT lpfDirectPoints[4] = {
				{ 0.0f, 20000.0f },    // リスナーからの距離が0メートルのときの低域フィルターのカットオフ周波数
				{ 10.0f, 15000.0f },   // リスナーからの距離が10メートルのときの低域フィルターのカットオフ周波数
				{ 20.0f, 10000.0f },   // リスナーからの距離が20メートルのときの低域フィルターのカットオフ周波数
				{ 30.0f, 5000.0f },    // リスナーからの距離が30メートルのときの低域フィルターのカットオフ周波数
			};

			lpfDirectCurve.pPoints = lpfDirectPoints;

			m_Emitter.pLPFDirectCurve = &lpfDirectCurve;

			X3DAUDIO_DISTANCE_CURVE lpfReverbCurve;
			lpfReverbCurve.PointCount = 4;  // ポイントの数

			X3DAUDIO_DISTANCE_CURVE_POINT lpfReverbPoints[4] = {
				{ 0.0f, 20000.0f },    // リスナーからの距離が0メートルのときのリバーブパスの低域フィルターのカットオフ周波数
				{ 10.0f, 15000.0f },   // リスナーからの距離が10メートルのときのリバーブパスの低域フィルターのカットオフ周波数
				{ 20.0f, 10000.0f },   // リスナーからの距離が20メートルのときのリバーブパスの低域フィルターのカットオフ周波数
				{ 30.0f, 5000.0f },    // リスナーからの距離が30メートルのときのリバーブパスの低域フィルターのカットオフ周波数
			};

			lpfReverbCurve.pPoints = lpfReverbPoints;

			m_Emitter.pLPFReverbCurve = &lpfReverbCurve;

			X3DAUDIO_DISTANCE_CURVE reverbCurve;
			reverbCurve.PointCount = 4;  // ポイントの数

			X3DAUDIO_DISTANCE_CURVE_POINT reverbPoints[4] = {
				{ 0.0f, 0.0f },    // リスナーからの距離が0メートルのときのリバーブ効果の強さ
				{ 10.0f, 0.5f },   // リスナーからの距離が10メートルのときのリバーブ効果の強さ
				{ 20.0f, 0.8f },   // リスナーからの距離が20メートルのときのリバーブ効果の強さ
				{ 30.0f, 1.0f },   // リスナーからの距離が30メートルのときのリバーブ効果の強さ
			};

			reverbCurve.pPoints = reverbPoints;

			m_Emitter.pReverbCurve = &reverbCurve;


			X3DAudioCalculate(m_X3DaudioHandle, &m_Listener, &m_Emitter, X3DAUDIO_CALCULATE_MATRIX, &m_DspSettings);

			m_Data.SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, m_DspSettings.pMatrixCoefficients);
		}
	}

}




void Audio::Play(bool Loop)
{
	m_Data.SourceVoice->Stop();
	m_Data.SourceVoice->FlushSourceBuffers();

	// バッファ設定
	XAUDIO2_BUFFER bufinfo = { 0 };


	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Data.Length;
	bufinfo.pAudioData = &m_Data.AudioData[0];
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_Data.PlayLength;

	// ループ設定
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_Data.PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_Data.SourceVoice->SubmitSourceBuffer(&bufinfo);

	// 再生
	m_Data.SourceVoice->Start();
}

void Audio::PlayStreaming(bool Loop)
{
	XAUDIO2_VOICE_STATE state;
	m_Data.SourceVoice->GetState(&state);

	if (state.BuffersQueued < 2)
	{
		DWORD flags = 0;
		BYTE* pAudioData = nullptr;
		DWORD audioDataLength = 0;
		DWORD streamIndex;
		LONGLONG llTimeStamp;

		m_SourceReader->ReadSample(
			MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			0,
			&streamIndex,
			&flags,
			&llTimeStamp,
			&m_Sample
		);

		if (m_Sample) {
			m_Sample->ConvertToContiguousBuffer(&m_Buffer);

			m_Buffer->Lock(&pAudioData, nullptr, &audioDataLength);

			XAUDIO2_BUFFER buffer = { 0 };
			buffer.AudioBytes = audioDataLength;
			buffer.pAudioData = pAudioData;
			buffer.Flags = XAUDIO2_LOOP_INFINITE;

			m_Data.SourceVoice->SubmitSourceBuffer(&buffer);

		}
	}

}


void Audio::FadeVolume(float index)
{

	float NowVloume{};
	m_Data.SourceVoice->GetVolume(&NowVloume);
	if (index <= NowVloume)
		NowVloume -= 0.02f;
	
	if (index >= NowVloume)
		NowVloume += 0.02f;
	
	m_Data.SourceVoice->SetVolume(NowVloume);
}

void Audio::SetEmitter(D3DXVECTOR3 forward,D3DXVECTOR3 up,D3DXVECTOR3 position,D3DXVECTOR3 velocity)
{
	m_Emitter.OrientFront = forward;
	m_Emitter.OrientTop = up;
	m_Emitter.Position = position;
	m_Emitter.Velocity = velocity;
}

