//=============================================================================
//
// ポリゴン表示処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "wall.h"
#include "texture.h"
#include "model.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model[4];			// モデル読み込み
static WALL			g_Wall[ALL_WALL_NUM][WALL_NUM];				// 壁情報		
static float		g_fream;
static float		g_speed;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWall(void)
{
	for (int n = 0; n < ALL_WALL_NUM; n++)
	{
		// 位置・回転・スケールの初期設定
		for (int i = 0; i < WALL_NUM; i++)
		{
			switch (i)
			{
			case 0:
				g_Wall[n][i].pos = D3DXVECTOR3(-195.0f, 110.0f, 1000.0f + 1000.0f * n);
				//objモデルの読み込み
				LoadModel((char*)"data/MODEL/red.obj", &g_Model[i]);
				g_Wall[n][i].color = 0;
				break;
			case 1:
				g_Wall[n][i].pos = D3DXVECTOR3(195.0f, 110.0f, 1000.0f + 1000.0f * n);
				//objモデルの読み込み
				LoadModel((char*)"data/MODEL/green.obj", &g_Model[i]);
				g_Wall[n][i].color = 1;
				break;
			case 2:
				g_Wall[n][i].pos = D3DXVECTOR3(-195.0f, -110.0f, 1000.0f + 1000.0f * n);
				//objモデルの読み込み
				LoadModel((char*)"data/MODEL/blue.obj", &g_Model[i]);
				g_Wall[n][i].color = 2;
				break;
			case 3:
				g_Wall[n][i].pos = D3DXVECTOR3(195.0f, -110.0f, 1000.0f + 1000.0f * n);
				//objモデルの読み込み
				LoadModel((char*)"data/MODEL/yellow.obj", &g_Model[i]);
				g_Wall[n][i].color = 3;
				break;
			}
			g_Wall[n][i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Wall[n][i].scl = D3DXVECTOR3(39.0f, 22.0f, 1.0f);
			g_Wall[n][i].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Wall[n][i].use = true;

			g_Wall[n][i].size = D3DXVECTOR3(400.0f, 200.0f, 50.0f);

			//方向を単位ベクトル化する
			D3DXVec3Normalize(&g_Wall[n][i].dir, &g_Wall[n][i].dir);


		}
	}

	g_speed = 5.0f;



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	//objモデルの解放
	for (int i = 0; i < WALL_NUM; i++)
	{
		UnloadModel(&g_Model[i]);
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{
	g_fream++;

	if (g_fream > 200.0f)
	{
		g_speed += 0.1f;
		g_fream = 0.0f;
	}
		
	
	for (int n = 0; n < ALL_WALL_NUM; n++)
	{
		for (int i = 0; i < WALL_NUM; i++)
		{
			g_Wall[n][i].pos.z -= g_speed;
			if (g_Wall[n][i].pos.z < -1000.0f)
			{
				g_Wall[n][i].pos.z = 10000.0f + 1000.0f * n;
				g_Wall[n][i].use = true;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int n = 0; n < ALL_WALL_NUM; n++)
	{
		for (int i = 0; i < WALL_NUM; i++)
		{
			//useフラグがオフの場合はスキップする5
			if (g_Wall[n][i].use == false)
				continue;

			// ワールドマトリックスの初期化（単位行列を作る関数）
			D3DXMatrixIdentity(&g_Wall[n][i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Wall[n][i].scl.x, g_Wall[n][i].scl.y, g_Wall[n][i].scl.z);
			D3DXMatrixMultiply(&g_Wall[n][i].mtxWorld, &g_Wall[n][i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[n][i].rot.y, g_Wall[n][i].rot.x, g_Wall[n][i].rot.z);
			D3DXMatrixMultiply(&g_Wall[n][i].mtxWorld, &g_Wall[n][i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Wall[n][i].pos.x, g_Wall[n][i].pos.y, g_Wall[n][i].pos.z);
			D3DXMatrixMultiply(&g_Wall[n][i].mtxWorld, &g_Wall[n][i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_Wall[n][i].mtxWorld);

			//objモデルの描画
			DrawModel(&g_Model[i]);
		}
	}
}


//=============================================================================
// 壁情報を取得
//=============================================================================
WALL *GetWall(int i)
{
	return &g_Wall[i][0];
}

