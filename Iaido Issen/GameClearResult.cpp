/*****************************************************************************
*
*    ゲームクリア画面　[GameClereResult.cpp]
*    作成者　　五十嵐郁哉
*
*    SE BGM導入　ウエマツ
******************************************************************************/
#include "GameClearResult.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "fade.h"
#include "sound1.h"

/*****************************************************************************
* マクロ定義
******************************************************************************/
enum SELECT
{
	SELECT_NONE,		// シーン設定なし
	SELECT_START,	//　タイトル
	SELECT_END,		// ゲーム本編

	SELECT_NUM,		// 終端コード
};

/*****************************************************************************
* プロトタイプ宣言
******************************************************************************/


/*****************************************************************************
* グローバル変数
******************************************************************************/
static int   g_GameClereResultTexture;  // テクスチャの識別子

static int   g_select;
static float g_count;

static int   g_GameClereSE = 0;		// BGM識別子

static int   g_Sound_husuma_op = 0;
static int   g_Sound_husuma_cl = 0;


/*****************************************************************************
* 初期化処理
******************************************************************************/
void InitGameClearResult(void)
{
	g_count = 0.0f;

	g_select = SELECT_START;

	// タイトル画面用テクスチャの読み込み
	g_GameClereResultTexture = LoadTexture((char*)"data/TEXTURE/result.jpg");
	
	g_GameClereSE = LoadSound((char*)"data/SE/GAMEClEAR.wav"); //タイトルBGM

	g_Sound_husuma_op = LoadSound((char*)"data/SE/襖の開く音.wav");
	g_Sound_husuma_cl = LoadSound((char*)"data/SE/襖の閉まる音.wav");


	//255(-1)をループ指定すると無限ループ
	PlaySound(g_GameClereSE, 0);


}

/*****************************************************************************
* 終了処理
******************************************************************************/
void UninitGameClearResult(void)
{

}

/*****************************************************************************
* 更新処理
******************************************************************************/
void UpdateGameClearResult(void)
{

	g_count += 0.5;

	if (g_count > 150)
	{
		SceneTransition(SCENE_TITLE);
		PlaySound(g_Sound_husuma_cl, 0); //襖の閉じる音
		PlaySound(g_Sound_husuma_op, 0); //襖の開く音
	}


}

/*****************************************************************************
* 描画処理
******************************************************************************/
void DrawGameClearResult(void)
{
	// テクスチャの描画
	DrawSpriteLeftTop(g_GameClereResultTexture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}