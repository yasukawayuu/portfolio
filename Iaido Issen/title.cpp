/*****************************************************************************
*
*    タイトル画面　[title.cpp]
*    作成者　　五十嵐郁哉
*
*    SE BGM導入　ウエマツ
******************************************************************************/
#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "inputx.h"
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

typedef struct
{
	D3DXVECTOR2		pos;
	int			use;
	float		vel;

}CLOUD;// 雲

/*****************************************************************************
* プロトタイプ宣言
******************************************************************************/


/*****************************************************************************
* グローバル変数
******************************************************************************/
static int   g_TitleBGTexture;  // テクスチャの識別子
static int   g_TitlePlayer;  // テクスチャの識別子
static int   g_TitleTitle;  // テクスチャの識別子
static int   g_TitleStartTexture;  // テクスチャの識別子
static int   g_TitleEndTexture;  // テクスチャの識別子
static int   g_TitleSelectTexture;  // テクスチャの識別子
static int   g_TitleCluudTexture1;  // テクスチャの識別子
static int   g_TitleCluudTexture2;  // テクスチャの識別子
static int   g_TitleButton;  // テクスチャの識別子

static CLOUD g_Cloud[1];
static CLOUD g_Cloud2[2];

//static float g_cloud_move1; // 雲の動き
//static float g_cloud_move2; // 雲の動き
static float g_s; // スタートボタンの緩急
static float g_amount; // スタートボタンの緩急
static float g_pos; // スタートボタンのポジション


static int   g_select;
static int   g_BGM_taitoru = 0;		// BGM識別子

static int   g_Sound_husuma_op = 0;
static int   g_Sound_husuma_cl = 0;
static int   g_Sound_move = 0;
static int   g_Sound_decision = 0;



/*****************************************************************************
* 初期化処理
******************************************************************************/
void InitTitle(void)
{
	g_Cloud[0].use = true;
	g_Cloud[0].pos.x = 30.0f;
	g_Cloud[0].pos.y = 100.0f;
	g_Cloud[0].vel = rand() % 3 + 4;

	for (int i = 0; i < 2; i++)
	{
		g_Cloud2[i].use = true;
		g_Cloud2[i].pos.x = 30.0f;
		g_Cloud2[i].pos.y = 100.0f;
		g_Cloud2[i].vel = rand() % 3 + 4;
	}


	//g_cloud_move1 = 0.0f;
	//g_cloud_move2 = 0.0f;
	g_s = 0.0f;
	g_amount = 0.0f;

	g_select = SELECT_START;

	// タイトル画面用テクスチャの読み込み
	g_TitleBGTexture = LoadTexture((char*)"data/TEXTURE/title/title_bg.png");
	g_TitlePlayer = LoadTexture((char*)"data/TEXTURE/title/title_player.png");
	g_TitleTitle = LoadTexture((char*)"data/TEXTURE/title/title_title.png");
	g_TitleStartTexture = LoadTexture((char*)"data/TEXTURE/title/start.png");
	g_TitleEndTexture = LoadTexture((char*)"data/TEXTURE/title/end.png");
	g_TitleSelectTexture = LoadTexture((char*)"data/TEXTURE/title/kursol.png");
	g_TitleCluudTexture1 = LoadTexture((char*)"data/TEXTURE/title/cloud_1.jpg");
	g_TitleCluudTexture2 = LoadTexture((char*)"data/TEXTURE/title/cloud_2.jpg");
	g_TitleButton = LoadTexture((char*)"data/TEXTURE/title/button.png");

	g_BGM_taitoru = LoadSound((char*)"data/BGM/タイトル.wav"); //タイトルBGM

	g_Sound_husuma_op = LoadSound((char*)"data/SE/襖の開く音.wav");
	g_Sound_husuma_cl = LoadSound((char*)"data/SE/襖の閉まる音.wav");
	g_Sound_move = LoadSound((char*)"data/SE/カーソル移動.wav");
	g_Sound_decision = LoadSound((char*)"data/SE/決定.wav");


	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGM_taitoru, -1);


}

/*****************************************************************************
* 終了処理
******************************************************************************/
void UninitTitle(void)
{
	StopSoundAll();
}

/*****************************************************************************
* 更新処理
******************************************************************************/
void UpdateTitle(void)
{
	if (g_Cloud[0].use == true)
	{
		g_Cloud[0].pos.x -= g_Cloud[0].vel;
	}
	//画面外に出たら上にリセット
	if (g_Cloud[0].pos.x < -80)
	{
		g_Cloud[0].vel = rand() % 3 + 4;
		g_Cloud[0].pos.y = rand() % 540 + 100;
		g_Cloud[0].pos.x = SCREEN_WIDTH + 100;
	}

	for (int k = 0; k < 2; k++)
	{
		if (g_Cloud2[k].use == true)
		{
			g_Cloud2[k].pos.x -= g_Cloud2[k].vel;
		}
		//画面外に出たら上にリセット
		if (g_Cloud2[k].pos.x < -80)
		{
			g_Cloud2[k].vel = rand() % 3 + 2;
			g_Cloud2[k].pos.y = rand() % 540 + 100;
			g_Cloud2[k].pos.x = SCREEN_WIDTH + 100;
		}
	}

	g_s = 0.15f; // スタートボタンの緩急値



	switch (g_select)
	{
	case SELECT_START:

		g_amount += g_s * g_s;

		g_pos += g_amount;

		if (g_pos >= 50)
		{
			g_amount = 0.0;
			g_pos = 0.0f;
		}
		break;
	case SELECT_END:
		g_pos = 0.0f;
		break;
	default:
		break;
	}


	if ((GetKeyboardTrigger(DIK_X)) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_DPAD_DOWN) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_DPAD_UP))
	{
		PlaySound(g_Sound_move, 0);
		if (g_select == SELECT_START)
		{
			g_select = SELECT_END;
		}
		else
		{
			g_select = SELECT_START;
		}
	}

	if ((g_select == SELECT_START) && ((GetKeyboardTrigger(DIK_SPACE)) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_A) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_B)))
	{
		// スペースキーでゲーム画面へ
		SceneTransition(SCENE_GAME);

		PlaySound(g_Sound_husuma_cl, 0); //襖の閉じる音

		//PlaySound(g_Sound_husuma_op, 0); //襖の開く音
	}
	if ((g_select == SELECT_END) && ((GetKeyboardTrigger(DIK_SPACE)) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_A) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_B)))
	{
		PostQuitMessage(WM_QUIT);
	}


}

/*****************************************************************************
* 描画処理
******************************************************************************/
void DrawTitle(void)
{
	// テクスチャの描画
	DrawSpriteLeftTop(g_TitleBGTexture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);


	DrawSprite(g_TitleCluudTexture1, g_Cloud[0].pos.x - g_Cloud[0].vel, g_Cloud[0].pos.y, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	for (int l = 0; l < 2; l++)
	{
		if (g_Cloud2[l].use == true)
		{
			DrawSprite(g_TitleCluudTexture2, g_Cloud2[l].pos.x - g_Cloud2[l].vel, g_Cloud2[l].pos.y, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		}
	}

	DrawSprite(g_TitleStartTexture, SCREEN_WIDTH / 4, 700.0f, 256.0f + g_pos, 120.0f + g_pos, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(g_TitleEndTexture, SCREEN_WIDTH / 4, 900.0f, 256.0f, 120.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(g_TitlePlayer, 980.0f, 500.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(g_TitleTitle, 800.0f, 400.0f, 1440, 720, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(g_TitleButton, 150.0f, 1000, 256, 96, 0.0f, 0.0f, 1.0f, 1.0f);

	switch (g_select)
	{
	case SELECT_START:
		DrawSprite(g_TitleSelectTexture, 300.0f, 700.0f, 128.0f, 128.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case SELECT_END:
		DrawSprite(g_TitleSelectTexture, 300.0f, 900.0f, 128.0f, 128.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

}