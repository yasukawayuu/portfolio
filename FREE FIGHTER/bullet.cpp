//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "camera.h"
#include "texture.h"
#include "shadow.h"
#include "color.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// 頂点バッファ

static BULLET		g_Bullet;	// 弾データ
static MATERIAL		g_Material;
static int			g_texNo = 0;


//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// 頂点バッファに値をセットする
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float width = 50.0f;
		float height = 50.0f;

		// 頂点座標の設定
		vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// 頂点カラーの設定
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	// テクスチャ生成
	g_texNo = LoadTexture((char*)"data/TEXTURE/bullet000.png");

	// マテリアル初期化
	ZeroMemory(&g_Material, sizeof(g_Material));
	g_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 初期化

	g_Bullet.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Bullet.dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Bullet.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_Bullet.color = frand() * 4;
	g_Bullet.use = false;

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	if(g_VertexBuffer != NULL)
	{// 頂点バッファの解放
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	if (g_Bullet.use)
	{
		//消滅処理
		if (g_Bullet.frame > 100.0f)
		{
			g_Bullet.use = false;

			//影を消す
			ReleaseShadow(g_Bullet.shadow);
		}

		//座標の更新
		g_Bullet.pos += g_Bullet.dir * g_Bullet.speed;

		//影の座標を更新する
		SetPositionShadow(g_Bullet.shadow, D3DXVECTOR3(g_Bullet.pos.x, 0.0f, g_Bullet.pos.z));

		//時間経過
		g_Bullet.frame += 1.0f;
	}
	
	AddColor(g_Bullet.color);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	// αテストを有効に
	SetAlphaTestEnable(true);

	// ライティングを無効
	SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if(g_Bullet.use)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Bullet.mtxWorld);

		CAMERA *cam = GetCamera();

		// ポリゴンを正面に向ける
#if 0
		// ビューマトリックスの逆行列を取得
		g_Bullet.mtxWorld = cam->mtxInvView;
		g_Bullet.mtxWorld._41 = 0.0f;
		g_Bullet.mtxWorld._42 = 0.0f;
		g_Bullet.mtxWorld._43 = 0.0f;
#else
		// ビューマトリックスを取得
		D3DXMATRIX mtxView = cam->mtxView;

		g_Bullet.mtxWorld._11 = mtxView._11;
		g_Bullet.mtxWorld._12 = mtxView._21;
		g_Bullet.mtxWorld._13 = mtxView._31;
		g_Bullet.mtxWorld._21 = mtxView._12;
		g_Bullet.mtxWorld._22 = mtxView._22;
		g_Bullet.mtxWorld._23 = mtxView._32;
		g_Bullet.mtxWorld._31 = mtxView._13;
		g_Bullet.mtxWorld._32 = mtxView._23;
		g_Bullet.mtxWorld._33 = mtxView._33;
#endif


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Bullet.pos.x,
											 g_Bullet.pos.y,
											 g_Bullet.pos.z);
		D3DXMatrixMultiply(&g_Bullet.mtxWorld, &g_Bullet.mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Bullet.mtxWorld);

		// マテリアル設定
		SetMaterial(g_Material);

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_texNo));

		// ポリゴンの描画
		GetDeviceContext()->Draw(4, 0);
	}
	

	// ライティングを有効に
	SetLightEnable(true);

	// αテストを無効に
	SetAlphaTestEnable(false);
}


//=============================================================================
// 弾のパラメータをセット
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{

	if (g_Bullet.use == false)
	{
		g_Bullet.pos = pos;
		g_Bullet.dir = dir;
		g_Bullet.frame = 0.0f;

		g_Bullet.speed = BULLET_SPEED;

		// 当たり判定用サイズを設定
		g_Bullet.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

		// 影の設定
		g_Bullet.shadow = SetShadow(D3DXVECTOR3(g_Bullet.pos.x, 0.0f, g_Bullet.pos.z), 50.0f);

		g_Bullet.use = true;


	}
		
}


BULLET* GetBullet(void)
{
	return &g_Bullet;
}
