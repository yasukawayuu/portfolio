//=============================================================================
//
// 地面処理 [player.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct PLAYER
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ

	int				shadow;		// 影の識別番号
	bool			RotateFlag;
	int				fream;


	float			Rot;		// キャラクターの向き
	float			Rotate;

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);


void SetPlyaer(void);
PLAYER *GetPlayer(void);
