//=============================================================================
//
// ポリゴン表示処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;	// モデル読み込み
static PLAYER		g_Player;	// プレイヤー情報		
static LIGHT		g_DirectionalLight;	// ディレクショナルライト
static LIGHT		g_PointLight[5];		// ポイントライト


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	// 位置・回転・スケールの初期設定
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.spd = 5.0f;
	g_Player.use = true;
	g_Player.Rot = 0.1f;
	g_Player.Rotate = 0.0f;
	g_Player.fream = 0;
	g_Player.RotateFlag = false;

	//当たり判定用サイズの初期設定
	g_Player.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/f15.obj", &g_Model);

	// 並行光源の設定（世界を照らす光）
	g_DirectionalLight.Type = LIGHT_TYPE_DIRECTIONAL;				// 並行光源
	g_DirectionalLight.Enable = true;								// このライトをON
	g_DirectionalLight.Direction = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);// 光の向き
	g_DirectionalLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 光の色
	SetLight(0, &g_DirectionalLight);								// これで設定している

	// 点光源の設定
	g_PointLight[0].Type = LIGHT_TYPE_POINT;						// 並行光源
	g_PointLight[0].Enable = true;									// このライトをON
	g_PointLight[0].Position = D3DXVECTOR4(0.0f, 0.0f, -400.0f, 0.0f);// 光の座標
	g_PointLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 光の色
	g_PointLight[0].Attenuation = 500000.0f;						// 減衰距離
	SetLight(1, &g_PointLight[0]);									// これで設定している


	// 影のセット（影は高さを0にして表示させる）
	g_Player.shadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), 80.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (g_Player.use)
	{
		//減衰処理
		if (g_Player.RotateFlag == false)
		{
			g_Player.rot.z *= 0.9f;
			g_Player.rot.x *= 0.9f;


			if (GetKeyboardPress(DIK_A) && g_Player.pos.x > -SCREEN_WIDTH / 3)
			{
				g_Player.pos.x += -VALUE_MOVE;
				g_Player.rot.z += g_Player.Rot;
			}

			if (GetKeyboardPress(DIK_D) && g_Player.pos.x < SCREEN_WIDTH / 3)
			{
				g_Player.pos.x += VALUE_MOVE;
				g_Player.rot.z -= g_Player.Rot;
			}

			if (GetKeyboardPress(DIK_W) && g_Player.pos.y < SCREEN_HEIGHT / 3)
			{
				g_Player.pos.y += VALUE_MOVE;
				g_Player.rot.x -= g_Player.Rot;
			}

			if (GetKeyboardPress(DIK_S) && g_Player.pos.y > -SCREEN_HEIGHT / 3)
			{
				g_Player.pos.y += -VALUE_MOVE;
				g_Player.rot.x += g_Player.Rot;
			}

		}
		
		if (GetKeyboardTrigger(DIK_LSHIFT) && GetKeyboardPress(DIK_D))
		{
			g_Player.RotateFlag = true;
			g_Player.spd = 10.0f;
			g_Player.Rotate = -0.1f;
		}


		if (GetKeyboardTrigger(DIK_LSHIFT) && GetKeyboardPress(DIK_A))
		{
			g_Player.RotateFlag = true;
			g_Player.spd = -10.0f;
			g_Player.Rotate = 0.1f;
		}

		if (g_Player.pos.x + g_Player.spd > SCREEN_WIDTH / 3 || g_Player.pos.x + -g_Player.spd < -SCREEN_WIDTH / 3)
			g_Player.spd = 0.0f;


		if (g_Player.RotateFlag == true)
		{
			g_Player.pos.x += g_Player.spd;
			g_Player.rot.z += g_Player.Rotate;
			g_Player.fream++;
			if (g_Player.fream >= 30)
			{
				g_Player.fream = 0;
				g_Player.RotateFlag = false;
			}
		}



		// 弾を撃つ
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			D3DXVECTOR3 dir;
			dir.x = cos(g_Player.rot.y - (D3DX_PI / 2));
			dir.y = 0.0f;
			dir.z = sin(g_Player.rot.y + (D3DX_PI / 2));
			SetBullet(g_Player.pos, dir);
		}

		// 影の位置を更新
		SetPositionShadow(g_Player.shadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
	}
	

#ifdef _DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Player.rot.x, g_Player.rot.y);

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	if (g_Player.use)
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Player.mtxWorld);

		//カリングなし(ミクさんモデルの髪の対応)
		SetCullingMode(CULL_MODE_NONE);

		//objモデルの描画
		DrawModel(&g_Model);

		//カリングを元に戻す
		SetCullingMode(CULL_MODE_BACK);
	}
	
}

//=============================================================================
// プレイヤー情報を取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
