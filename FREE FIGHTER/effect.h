#pragma once
//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


// バレット構造体
struct EFFECT
{
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:使っている  false:未使用
	D3DXVECTOR3				pos;	// バレットの座標
	D3DXVECTOR3				dir;	// バレットの移動方向
	float					frame;	// フレーム数

	float					uw, vh;
	int						u, v;

	D3DXVECTOR3     size;		// 当たり判定用サイズ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos);

