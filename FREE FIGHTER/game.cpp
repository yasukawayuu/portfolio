/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "color.h"
#include "effect.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// カメラの初期化
	InitCamera();

	// 影の初期化
	InitShadow();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 100.0f, 100.0f);

	//壁の初期化
	InitWall();

	// プレイヤーの初期化
	InitPlayer();

	// エネミーの初期化
	//InitEnemy();

	//エフェクトの初期化
	InitEffect();

	// 弾の初期化
	InitBullet();

	// スコアの初期化
	InitScore();

	//色の初期化
	InitColor();

	SetLightEnable(true);

	g_BGMNo = LoadSound((char*)"data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);
	PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	//初期化とは逆順に終了処理を行う
	UninitScore();
	UninitShadow();
	UninitBullet();
	//UninitEnemy();
	UninitWall();
	UninitPlayer();
	UninitColor();
	UninitMeshField();
	UninitEffect();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	// カメラ更新
	UpdateCamera();

	// 地面の更新処理
	UpdateMeshField();

	// プレイヤーの更新処理
	UpdatePlayer();

	// エネミーの更新処理
	//UpdateEnemy();

	//エフェクトの更新処理
	UpdateEffect();

	//壁の更新処理
	UpdateWall();

	// 弾の更新処理
	UpdateBullet();

	// 影の更新処理
	UpdateShadow();

	// スコアの更新処理
	UpdateScore();

	//色の更新処理
	UpdateColor();
	
	// 当たり判定の更新処理
	UpdateCollision();

}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// プレイヤー視点
	D3DXVECTOR3 pos = GetPlayer()->pos;
	pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
	//SetCameraAT(pos);
	SetCamera();

	// 深度テスト有効
	SetDepthEnable(true);

	// ライティング有効
	SetLightEnable(true);

	//エフェクトの描画処理
	DrawEffect();

	// 地面の描画処理
	DrawMeshField();

	//壁の描画処理
	DrawWall();

	// 影の描画処理
	DrawShadow();

	// エネミーの描画処理
	//DrawEnemy();

	// プレイヤーの描画処理
	DrawPlayer();

	// 弾の描画処理
	DrawBullet();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// スコアの描画処理
	DrawScore(D3DXVECTOR2(900.0f, 30.0f));

	//　色の描画処理
	DrawColor();
}

