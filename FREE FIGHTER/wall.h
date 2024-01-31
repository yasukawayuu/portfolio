//=============================================================================
//
// 地面処理 [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WALL_NUM 4
#define ALL_WALL_NUM 10

struct WALL
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		dir;		// 移動方向
	int				color;

	bool			use;		// 表示フラグ

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall (void);
void DrawWall(void);

WALL *GetWall(int i);
