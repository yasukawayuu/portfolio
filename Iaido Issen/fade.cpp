//=============================================================================
//
// フェード処理 [fade.cpp]
// 
//
//=============================================================================
#include "fade.h"
#include "texture.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FADE_RATE					(0.01f)			// フェード係数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TextureFade;				// テクスチャ番号
static int	g_TextureFadeL;				// テクスチャ番号
static int	g_TextureFadeR;				// テクスチャ番号


FADE_STATE	g_FadeState = FADE_NONE;	// フェードの状態
SCENE		g_SceneNext;				// 次のシーン
//D3DXCOLOR	g_Color;					// フェードのカラー
float g_move;
int g_flag;
float g_count;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFade(void)
{
	//テクスチャ生成
	//g_TextureFade = LoadTexture((char*)"data/TEXTURE/husuma.jpg");
	g_TextureFadeL = LoadTexture((char*)"data/TEXTURE/husuma/husumaL.jpg");
	g_TextureFadeR = LoadTexture((char*)"data/TEXTURE/husuma/husumaR.jpg");

	//初期化
	g_FadeState = FADE_NONE;
	g_SceneNext = SCENE_NONE;
	//g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	g_move = 0.0f;
	g_flag = 0;
	g_count = 0.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	

	// フェード処理中
	if (g_FadeState != FADE_NONE)
	{
		
		if (g_FadeState == FADE_OUT)
		{// フェードアウト処理

			g_move += 20;
			if (g_move >= SCREEN_WIDTH / 2 && g_flag == 0)
			{
				g_flag = 1;
				g_move = 0;

			}
			if (g_flag == 1)
			{
				// フェードイン処理に切り替え
				g_FadeState = FADE_IN;

				// モードを設定
				SetScene(g_SceneNext);
				
			}

			
		}
		else if (g_FadeState == FADE_IN)
		{// フェードイン処理

			g_move += 20;
			if (g_move >= SCREEN_WIDTH / 2)
			{
				g_move = 0;
				g_flag = 0;
				g_FadeState = FADE_NONE;
			}
		}		
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	// フェード処理をしていないのなら描画しない
	if (g_FadeState == FADE_NONE)
		return;

	if (g_flag == 0)
	{
		DrawSprite(g_TextureFadeL, (-SCREEN_WIDTH / 4 + g_move), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawSprite(g_TextureFadeR, (SCREEN_WIDTH + (SCREEN_WIDTH / 4)) - g_move, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	if (g_flag == 1)
	{
		DrawSprite(g_TextureFadeL, (SCREEN_WIDTH / 4 - g_move), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawSprite(g_TextureFadeR, ((SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4) + g_move), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	

}

/*------------------------------------------------------------------------------
   フェードアウト・フェードイン処理をしながらシーン遷移する関数
------------------------------------------------------------------------------*/
void SceneTransition(SCENE nextScene)
{
	g_SceneNext = nextScene;
	g_FadeState = FADE_OUT;

	// FADE_OUT → FADE_IN
}

/*------------------------------------------------------------------------------
   フェードイン処理をしながらシーンを開始する関数
------------------------------------------------------------------------------*/
void SceneFadeIn(SCENE nextScene)
{
	//g_Color.a = 1.0f;
	g_FadeState = FADE_IN;
	SetScene(nextScene);

	// いきなり FADE_IN
}

/*------------------------------------------------------------------------------
   フェード処理の状況を返す関数
------------------------------------------------------------------------------*/
FADE_STATE GetFadeState(void)
{
	return g_FadeState;
}

/*------------------------------------------------------------------------------
   フェードカラー設定する関数
------------------------------------------------------------------------------*/
void SetFadeColor(float r, float g, float b)
{
	//g_Color = D3DXCOLOR(r, g, b, 1.0f);
}

