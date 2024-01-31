#pragma once

#include "main.h"

class EFFECT
{
private:
	int m_TextureKyuubiSand = 0;    //九尾の攻撃時の砂埃用テクスチャの識別子
	int m_TextureSlash = 0;         //スラッシュ用テクスチャの識別子
	int m_TextureBlood = 0;         //血液テクスチャの識別子
	int m_TextureCharge = 0;        //チャージテクスチャの識別子
	int m_TextureDeath = 0;         //死亡時演出テクスチャの識別子
	int m_TextureHit = 0;           //ヒットテクスチャの識別子
	int m_TextureOverheat = 0;      //オーバーヒートテクスチャの識別子
	int m_TextureRun = 0;           //通常移動時テクスチャの識別子
	int m_TextureTeleportation = 0; //瞬間移動時テクスチャの識別子
	int m_TextureKyuubiTele = 0;    //九尾の瞬間移動時のテクスチャ識別子
	int m_TextureKyuubiCharge;      //九尾が魔力を溜めるときのテクスチャの識別子
	
	int m_Flag;


	
	D3DXVECTOR2 *m_base;			//カメラ
	
	struct Effect
	{
		D3DXVECTOR2 pos;                     //エフェクトのポジション
		D3DXVECTOR2 wh;                      //エフェクトの大きさ
		bool        use;		             //エフェクトの表示
		float       time;	                 //エフェクトの表示時間
		int         muki;		             //エフェクトの向き
		int			animePtn;				 //エフェクトの動きの切り替え
		int			animeReservoirPtn;		 //予測するときのアニメーション
		int			animeCounter;			 //エフェクトの動きの速さのベースをゲットした
		D3DXVECTOR2 divide;                  //エフェクトのアニメーションの分割数
		D3DXVECTOR2 patternWH;               //エフェクトのパターン数
		int         patternMax;              //エフェクトの最大アニメーション数
		int         patternWait;             //エフェクトのアニメーションウェイト
	};

	float m_mukiTalbelSlash[4]
	{
		D3DX_PI / 2,
		0.0f,
		D3DX_PI / 2,
		0.0f,
	};

	float m_mukiTalbelTeleportation[4]
	{
		D3DX_PI,
		0.0f,
		D3DX_PI,
		0.0f,
	};

	Effect m_KyuubiSand;         //九尾のしっぽ攻撃時の砂埃
	Effect m_Slash;              //斬撃
	Effect m_Blood;              //血液
	Effect m_Charge;              //チャージ
	Effect m_Death;              //死亡時演出
	Effect m_Hit;                //ヒット
	Effect m_Overheat;           //オーバーヒート
	Effect m_Run;                //通常移動時
	Effect m_Teleportation;      //瞬間移動
	Effect m_KyuubiTele;         //九尾の瞬間移動
	Effect m_KyuubiCharge;       //九尾の魔力溜め

public:
	EFFECT() {}
	EFFECT(D3DXVECTOR2 *base) : m_base(base) {}
	~EFFECT() {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetKyuubiSand(D3DXVECTOR2 pos);
	void SetSlashEffect(D3DXVECTOR2 pos,int muki);
	void SetBlood(D3DXVECTOR2 pos);
	void SetCharge(D3DXVECTOR2 pos);
	void SetDeath(D3DXVECTOR2 pos);
	void SetHit(D3DXVECTOR2 pos);
	void SetOverheat(D3DXVECTOR2 pos);
	void SetRun(D3DXVECTOR2 pos);
	void SetTeleportation(D3DXVECTOR2 pos);
	void SetKyuubiTele(D3DXVECTOR2 pos);
	void SetKyuubiCharge(D3DXVECTOR2 pos);



	void ResetKyuubiSand(void);
	void ResetSlash(void);
	void ResetBlood(void);
	void ResetCharge(void);
	void ResetDeath(void);
	void ResetHit(void);
	void ResetOverheat(void);
	void ResetRun(void);
	void ResetTeleportation(void);
	void ResetKyuubiTele(void);
	void ResetKyuubiCharge(void);
	

	Effect* GetKyuubiSand(void) { return &m_KyuubiSand; }
	Effect* GetSlash(void) { return &m_Slash; }
	Effect* GetBlood(void) { return &m_Blood; }
	Effect* GetCharge(void) { return &m_Charge; }
	Effect* GetDeath(void) { return &m_Death; }
	Effect* GetHit(void) { return &m_Hit; }
	Effect* GetOverheat(void) { return &m_Overheat; }
	Effect* GetRun(void) { return &m_Run; }
	Effect* GetTeleportation(void) { return &m_Teleportation; }

	void SetFlag(int flag);
};