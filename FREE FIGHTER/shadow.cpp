//=============================================================================
//
// 影処理 [shadow.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shadow.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SHADOW_SIZE_X		(1.0f)			// 頂点サイズ
#define	SHADOW_SIZE_Z		(1.0f)			// 頂点サイズ

#define	MAX_SHADOW			(1024)			// 影最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXMATRIX	mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scl;		// スケール
	MATERIAL	material;	// マテリアル
	bool		use;		// 使用しているかどうか

} SHADOW;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// 頂点情報

static SHADOW			g_aShadow[MAX_SHADOW];		// 影ワーク
static int				g_texNo;					// テクスチャ番号

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitShadow(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	{//頂点バッファの中身を埋める
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// 頂点座標の設定
		vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
		vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

		// 法線の設定
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	// テクスチャ生成
	g_texNo = LoadTexture((char*)"data/TEXTURE/shadow000.jpg");

	// 影ワーク初期化
	for(int i = 0; i < MAX_SHADOW; i++)
	{
		ZeroMemory(&g_aShadow[i].material, sizeof(g_aShadow[i].material));
		g_aShadow[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_aShadow[i].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		g_aShadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aShadow[i].use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	// 減算合成
	SetBlendState(BLEND_MODE_SUBTRACT);

	// Z比較なし
	SetDepthEnable(false);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_texNo));

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for(int i = 0; i < MAX_SHADOW; i++)
	{
		if(g_aShadow[i].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_aShadow[i].scl.x, g_aShadow[i].scl.y, g_aShadow[i].scl.z);
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld, &g_aShadow[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[i].rot.y, g_aShadow[i].rot.x, g_aShadow[i].rot.z);
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld, &g_aShadow[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aShadow[i].pos.x, g_aShadow[i].pos.y, g_aShadow[i].pos.z);
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld, &g_aShadow[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_aShadow[i].mtxWorld);

			// マテリアルの設定
			SetMaterial(g_aShadow[i].material);

			// ポリゴンの描画
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// 通常ブレンド
	SetBlendState(BLEND_MODE_ALPHABLEND);
	
	// Z比較あり
	SetDepthEnable(true);
}

//=============================================================================
// 影の作成
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, float size)
{
	int index = -1;

	for(int i = 0; i < MAX_SHADOW; i++)
	{
		// 未使用（false）だったらそれを使う
		if(!g_aShadow[i].use)
		{
			g_aShadow[i].pos = pos;
			g_aShadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aShadow[i].scl = D3DXVECTOR3(size, 1.0f, size);
			g_aShadow[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aShadow[i].use = true;

			index = i;	// これがIndex番号
			break;
		}
	}

	return index;	// Index番号を返している
}

//=============================================================================
// マテリアルカラーの設定
//=============================================================================
void SetColorShadow(int index, D3DXCOLOR col)
{
	if (index >= 0 && index < MAX_SHADOW)
	{
		g_aShadow[index].material.Diffuse = col;
	}
}

//=============================================================================
// 影の破棄
//=============================================================================
void ReleaseShadow(int index)
{
	if(index >= 0 && index < MAX_SHADOW)
	{
		g_aShadow[index].use = false;
	}
}

//=============================================================================
// 位置の設定
//=============================================================================
void SetPositionShadow(int index, D3DXVECTOR3 pos)
{
	if (index >= 0 && index < MAX_SHADOW)
	{
		g_aShadow[index].pos = pos;
	}
}

