/*==============================================================================

   テクスチャの描画 [main.cpp]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include <time.h>
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "sound1.h"
#include "title.h"
#include "fade.h"
#include "GameClearResult.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"居合道『一閃』"			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void ChangeScene(void);

GAME game;

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用

#endif

static SCENE g_Scene;		// シーン制御
static SCENE g_SceneNext;   // 移行先のシーン
											//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				// 現在のシーンとネクストシーンが食い違っていたら
				if (g_Scene != g_SceneNext)
				{
					// シーンの切り替えを行う
					ChangeScene();
				}

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);
	InitInput_X(hInstance, hWnd);
	
	// スプライト処理の初期化
	InitSprite();

	// フェード処理の初期化
	InitFade();

	// 初期シーンを初期化する
	g_Scene = g_SceneNext = SCENE_NONE;
	
	SetScene(SCENE_TITLE);

	InitSound(hWnd);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{

	game.Uninit();


	// フェード処理の終了処理
	UninitFade();

	// テクスチャの終了処理
	UninitTexture();

	// 入力処理の終了処理
	UninitInput();
	UninitInput_X();

	// サウンドの終了処理
	StopSoundAll();
	UninitSound();
	// レンダリングの終了処理
	UninitRenderer();

	// スプライト処理の解放
	UninitSprite();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力処理の更新処理
	UpdateInput();
	UpdateInput_X();


	// 現在のシーンを更新させる
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_GAME:
		game.Update();
		break;
	case SCENE_RESULT:
		UpdateGameClearResult();
		break;
	}

	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// 現在のシーンを更新させる
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_GAME:
		game.Draw();
		break;
	case SCENE_RESULT:
		DrawGameClearResult();
		break;
	}

	// フェードの描画は一番最後
	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}

float frand(void)
{
	return (float)rand() / RAND_MAX;
}


void SetScene(SCENE nextScene)
{
	g_SceneNext = nextScene;
}

void ChangeScene(void)
{
	// 現在のシーンを終了させる
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_GAME:
		game.Uninit();
		break;
	case SCENE_RESULT:
		UninitGameClearResult();
		break;
	}

	// 現在のシーンを更新する
	g_Scene = g_SceneNext;

	// 更新されたシーンを初期化させる
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_GAME:
		game.Init();
		break;
	case SCENE_RESULT:
		InitGameClearResult();
		break;
	}
}
