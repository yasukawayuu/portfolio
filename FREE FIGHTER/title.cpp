//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_TextureStart = 0;	// テクスチャ情報
static int	g_TextureExit = 0;	// テクスチャ情報
static int  g_TextureSelect = 0;
static int	g_TextureBg = 0;

static D3DXVECTOR2  g_SelectPos;
static int	g_BGMNo = 0;		// BGM識別子

								//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/freefighter.png");

	g_TextureStart = LoadTexture((char*)"data/TEXTURE/start.png");

	g_TextureExit = LoadTexture((char*)"data/TEXTURE/exit.png");

	g_TextureSelect = LoadTexture((char*)"data/TEXTURE/select.png");

	g_TextureBg = LoadTexture((char*)"data/TEXTURE/bg.jpeg");

	g_BGMNo = LoadSound((char*)"data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, -1);

	g_SelectPos = D3DXVECTOR2(SCREEN_WIDTH / 2 - 120.0f, SCREEN_HEIGHT / 2 + 70.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_S) && g_SelectPos.y == SCREEN_HEIGHT / 2 + 70.0f)
	{
		g_SelectPos.y += 70.0f;
	}

	if (GetKeyboardTrigger(DIK_W) && g_SelectPos.y == SCREEN_HEIGHT / 2 + 140.0f)
	{ 
		g_SelectPos.y -= 70.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		if(g_SelectPos.y == SCREEN_HEIGHT / 2 + 70.0f)
			SceneTransition(SCENE_GAME);

		if (g_SelectPos.y == SCREEN_HEIGHT / 2 + 140.0f)
			exit(0);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureBg, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,0.0f , 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureNo, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 300.0f, 300.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureStart, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 75.0f, 200.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureExit, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150.0f, 200.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureSelect,g_SelectPos.x,g_SelectPos.y, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f);

}

