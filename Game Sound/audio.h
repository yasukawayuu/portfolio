#pragma once

#include "component.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <xaudio2.h>
#include <X3DAudio.h>
#include <vector>
#include <string>

#pragma comment (lib, "mfplat.lib")
#pragma comment (lib, "mfuuid.lib")
#pragma comment (lib, "mfreadwrite.lib")


#define SPEED_OF_SOUND 343.5f

enum AudioMode
{
	AUDIO_2D,
	AUDIO_3D
};

struct Data
{
	std::string				Name{};
	std::vector<BYTE>		AudioData{};
	int						Length{};
	int						PlayLength{};
	IXAudio2SourceVoice*	SourceVoice{};
};


class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	static X3DAUDIO_HANDLE			m_X3DaudioHandle;
	
	IMFSourceReader*				m_SourceReader{};
	IMFMediaType*					m_NativeType{};
	IMFSample*						m_Sample{};
	IMFMediaBuffer*					m_Buffer{};

	X3DAUDIO_LISTENER				m_Listener{};
	X3DAUDIO_EMITTER				m_Emitter{};

	X3DAUDIO_DSP_SETTINGS			m_DspSettings{};

	unsigned int			m_Index{};
	float					m_OverallVolume{};
	bool					m_SoundFade{};
	bool					m_IsSoundEnd = true;
	
	Data					m_Data{};

	XAUDIO2_VOICE_STATE		m_State{};
	AudioMode				m_AudioMode = AUDIO_2D;
public:
	static void InitMaster();
	static void UninitMaster();

	using Component::Component;

	void Init(AudioMode audioMode = AUDIO_2D);
	void Uninit();
	void Update();
	void LoadSoundFile(const wchar_t* filename);
	void Load(const wchar_t* filename);
	void Play(bool Loop = false);
	void PlayStreaming(bool Loop = false);
	void FadeVolume(float index);
	void SetEmitter(D3DXVECTOR3 forward, D3DXVECTOR3 up, D3DXVECTOR3 position, D3DXVECTOR3 velocitys);
	
	float GetVolume()
	{
		float NowVloume{};
		m_Data.SourceVoice->GetVolume(&NowVloume);
		return NowVloume;
	}
	void SetVolume(float volume){ m_Data.SourceVoice->SetVolume(volume); }

	Data GetData () const { return m_Data; }
	void SetData(const Data &data) { m_Data = data; }
	void SetDataName(std::string name) { m_Data.Name = name; }
	bool GetSoundEnd() const { return m_IsSoundEnd; }
	void SetIndex(unsigned int index) { m_Index = index; }
	unsigned int GetIndex() const { return m_Index; }
};

//mp3,ogg対応　△
//サウンドエンジン対応　しない
//(ADX2,Wwise)
//ストリーミング再生　×
//3Dサウンド、立体音響 〇