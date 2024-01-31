//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "bullet.h"
#include "wall.h"
#include "shadow.h"
#include "score.h"
#include "wall.h"
#include "player.h"
#include "color.h"
#include "effect.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


void Collision_Bullet_Wall(void);
void Collision_Player_Wall(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
	Collision_Bullet_Wall();

	Collision_Player_Wall();
}


void Collision_Bullet_Wall(void)
{
	BULLET *bullet = GetBullet();	// 弾のポインターを初期化

	//使用されていない弾は何もしない
	if (bullet->use)
	{
		for (int i = 0; i < ALL_WALL_NUM; i++)
		{
			WALL  *wall = GetWall(i);		// エネミーのポインターを初期化

			for (int n = 0; n < WALL_NUM; n++)
			{
				//使用されていない敵は何もしない
				if (wall[n].use == false)
					continue;

				if (CollisionBB(bullet->pos, wall[n].pos, bullet->size, wall[n].size))
				{
					if (wall[n].color == bullet->color)
					{
						// 点数を加算する
						AddScore(10);
						//　壁を消す
						wall[n].use = false;
						bullet->color = frand() * 4;
					}
					
					// 弾を消す
					bullet->use = false;
					ReleaseShadow(bullet->shadow);

				
				}
			}
		}
	}
}

void Collision_Player_Wall(void)
{
	PLAYER *player = GetPlayer();	// 弾のポインターを初期化

	for (int i = 0; i < ALL_WALL_NUM; i++)
	{
		WALL  *wall = GetWall(i);		// エネミーのポインターを初期化

		for (int n = 0; n < WALL_NUM; n++)
		{
			//使用されていない敵は何もしない
			if (wall[n].use == false)
				continue;

			if (CollisionBB(player->pos, wall[n].pos, player->size, wall[n].size))
			{
				wall[n].use = false;
				// プレイヤーを消す
				player->use = false;
				SetEffect(player->pos);
				ReleaseShadow(player->shadow);

				SceneTransition(SCENE_RESULT);
			}
		}
	}
}

//=============================================================================
// 境界箱(BB)による当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	float Axmax = pos1.x + (size1.x / 2);
	float Axmin = pos1.x - (size1.x / 2);
	float Aymax = pos1.y + (size1.y / 2);
	float Aymin = pos1.y - (size1.y / 2);
	float Azmax = pos1.z + (size1.z / 2);
	float Azmin = pos1.z - (size1.z / 2);

	float Bxmax = pos2.x + (size2.x / 2);
	float Bxmin = pos2.x - (size2.x / 2);
	float Bymax = pos2.y + (size2.y / 2);
	float Bymin = pos2.y - (size2.y / 2);
	float Bzmax = pos2.z + (size2.z / 2);
	float Bzmin = pos2.z - (size2.z / 2);

	if ((Axmax > Bxmin) && (Axmin < Bxmax))
	{
		if ((Aymin < Bymax) && (Aymax > Bymin))
		{
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// 境界球(BS)による当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR3 dist = pos2 - pos1;

	//作ったベクトルの大きさを計算する
//	float length = D3DXVec3Length(&dist);

	//Sqがついている関数は平方根の計算をしないバージョン
	float length = D3DXVec3LengthSq(&dist);

	//1と2の半径を足す
//	float size = size1 + size2;

	//平方根の計算をしないので判定する相手の方を二乗する
	float size = (size1 + size2) * (size1 + size2);

	//半径の方が大きいとき、二つの円は重なっている
	if (length < size)
		return true;

	return false;
}
