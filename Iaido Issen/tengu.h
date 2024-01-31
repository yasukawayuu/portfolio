#pragma once

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define DIVIDE_ENEMY_X 3     //敵の横の分割数
#define DIVIDE_ENEMY_Y 2     //敵の縦の分割数

#define PATTERN_ENEMY_WIDTH5 (1.0f / 5)         //敵のuの横幅
#define PATTERN_ENEMY_WIDTH4 (1.0f / 4)         //敵のuの横幅
#define PATTERN_ENEMY_WIDTH3 (1.0f / 3)         //敵のuの横幅
#define PATTERN_ENEMY_WIDTH2 (1.0f / 2)         //敵のuの横幅

#define PATTERN_ENEMY_HEIGHT (1.0f / DIVIDE_ENEMY_Y)        //敵のvの高さ

#define THUNDER_DOWN_FRAME (100)	// 感電状態になっているフレーム
#define HIT_FRAME	(50)		// 被弾テクスチャを表示するフレーム数
#define DOWN_FRAME	(500)		// ダウンしているフレーム数

#define GROUND_POS (780.0f)

#define THUNDER_FRAME (200.0f) //雷が落ちるまでのフレーム数

#define FIRE_SPEED (4.0f)	// 炎のスピード

#define ANIMATION_COUNT (7)	// アニメーションを更新するまでのフレーム数

#define THUNDER_HIT_SIZE (100.0f)	// 雷との当たり判定の大きさ

#define GROUNDLINE 845





enum TENGU_STATE {
	TENGU_STATE_NONE,	      //シーン設定なし
	TENGU_STATE_STAY,         //待機
	TENGU_STATE_THUNDER1,      //雷
	TENGU_STATE_THUNDER2,      //雷
	TENGU_STATE_THUNDER3,      //雷
	TENGU_STATE_FIRE,	      //火
	TENGU_STATE_WIND,         //風
	TENGU_STATE_PARTURITION,  //分身

	TENGU_STATE_NUM,	      //終端コード
};


class TENGU
{
private:
	int	m_TextureTenguHp0;			// HP(黒)テクスチャ識別子
	int	m_TextureTenguHp1;			// HPテクスチャ識別子
	int	m_TextureTenguNomal;		// 天狗(待機)テクスチャ識別子
	int	m_TextureTenguThunderAtk;	// 天狗(雷)テクスチャ識別子
	int	m_TextureTenguThunder;		// 天狗(雷)テクスチャ識別子
	int	m_TextureTenguFall;			// 天狗(落下)テクスチャ識別子
	int m_TextureTenguDown;			// 天狗(ダウン)テクスチャ識別子
	int	m_TextureTenguFire;			// 天狗(炎攻撃)テクスチャ識別子
	int	m_TextureTenguWind;			// 天狗(風攻撃)テクスチャ識別子
	int m_TextureTenguHit;			// 天狗(被弾)テクスチャ識別子
	int	m_TextureCloud;	            // 雲テクスチャ識別子
	int	m_TextureThunder;	        // 雷テクスチャ識別子
	int	m_TextureFire;	            // 火テクスチャ識別子
	int	m_TextureWind;	            // 風テクスチャ識別子
	int	m_TextureExp;	            // 爆発テクスチャ識別子

	bool m_TenguAtSoundFlag1;
	bool m_TenguAtSoundFlag2;
	bool m_TenguAtSoundFlag3;
	bool m_TenguAtSoundFlag4;
	bool m_TenguAtSoundFlag5;
	bool m_TenguAtSoundFlag6;
	bool m_TenguBGMSoundFlag;



	struct TENGU_KOUZOUTAI
	{
		D3DXVECTOR2		pos;          //ポジション

		D3DXVECTOR2		dir;          //移動方向
		float			speed;        //移動スピード
		float			vel;

		int				hp;

		int			    muki;         //向き
		float			originalPosx; //座標Xの初期値


		bool			swingUpFlag;   //振り上げるフラグ
		bool			swingDownFlag; //振りおろすフラグ

		bool			nomalFlag;		// 待機モーションを再生 (テクスチャ)

		bool			thunderAtkFrag;		// 雷攻撃をしている (テクスチャ)
		bool			thunderHitFlag;		// 雷が当たったフラグ (テクスチャ)
		int				thunderDownFrame;	// 雷で動けなくなるフレーム数

		bool			downFlag;			// ダウンしているフラグ (テクスチャ)
		int				downFrame;			// ダウンしているフレーム数

		bool			fallFlag;			// 落ちるフラグ (テクスチャ)

		bool			fireFlag;			// 炎攻撃フラグ (テクスチャ)

		bool			windFlag;			// 風攻撃フラグ (テクスチャ)

		bool			atkFlag;			// 攻撃を受けるか
		bool			hitFlag;			// 攻撃を受けたか
		bool			texHitFlag;			// ヒットテクスチャを表示するか (テクスチャ)
		int				hitFrame;			// ヒットテクスチャを表示するフレーム数

		bool			ReturnNomalFlag;		// 元の位置へ戻る

		bool			move;			// 被弾などで動けない時にfalse

		float				animePtn;      //コマ数
		int				animeCounter;  //コマ描画までのカウント

		bool 			use;           //可視フラグ
		float			frame;         //進んだフレーム数

		int             stateteng;     //天狗の状態

		
	};
	
    int m_rand[3];
    int m_randPre[3];
   
    int r;
    int rPre;
   
   
    float  m_bulletCount = 0.0f;          //弓が発射されるまでをカウント
    float  m_shildCount = 0.0f;           //盾が突進するまでをカウント

	float m_AnimeTable[4] =			//敵のuv値
	{
		0.0f,
		0.3333f,
		0.6666f,
		0.3333f,
	};

	float m_MukiTable[2] =
	{
		0.5f,	//左向き
		0.0f,	//右向き
	};
	

	struct CLOUD
	{
		D3DXVECTOR2		pos;          //ポジション

		float			frame;        //進んだフレーム数
		float			anmPtn;
		int				anmFrame;

		bool 			use;          //可視フラグ

	};
	struct THUNDER
	{
		D3DXVECTOR2		pos;          //ポジション

		float			frame;        //進んだフレーム数

		bool 			use;          //可視フラグ

	};
	struct FIRE
	{
		D3DXVECTOR2		pos;          //ポジション
		D3DXVECTOR2		prepos;       //予測ポジション
		D3DXVECTOR2     dir;          //方向ベクトル
		D3DXVECTOR2     vDist;        //2点間の距離(計算)

		float			frame;        //進んだフレーム数
		float           speed;        //火の速さ
		float           len;          //2点間の距離

		bool 			use;          //可視フラグ
		bool            onGround;     //火が地面についたかのフラグ
	};

	struct WIND
	{
		D3DXVECTOR2		pos;          //ポジション
		D3DXVECTOR2		speed;        //速さ


		float			frame;        //進んだフレーム数

		bool 			use;          //可視フラグ

	};

	struct EXP
	{
		D3DXVECTOR2		pos;          //ポジション

		float	anmPtn;
		int		anmFrame;

		bool 			use;          //可視フラグ

	};

	TENGU_KOUZOUTAI m_Tengu;				      //天狗バッファ
	CLOUD m_Cloud;                     //雲バッファ
	THUNDER m_Thunder;                 //雷バッファ
	FIRE  m_Fire[3];                   //火バッファ
	WIND  m_Wind[2];                   //風バッファ


	TENGU_KOUZOUTAI m_TenguPre;				  //天狗分身バッファ
	CLOUD m_CloudPre;                  //雲分身バッファ
	THUNDER m_ThunderPre;              //雷分身バッファ
	FIRE  m_FirePre[3];                //火分身バッファ
	WIND  m_WindPre[2];                //風分身バッファ

	EXP  m_Exp;

	D3DXVECTOR2 *m_playerpos;
	D3DXVECTOR2	*m_base;

public:
	TENGU(D3DXVECTOR2 *pos, D3DXVECTOR2* base) :m_playerpos(pos), m_base(base) {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void TenguPattenrn(void);           //天狗の状態遷移
	void TenguState_Stay(void);         //天狗待機状態
	void TenguState_Thunder(void);      //天狗雷攻撃状態
	void TenguState_Fire(void);         //天狗の火攻撃状態
	void TenguState_Wind(void);         //天狗の風攻撃状態
	void TenguState_Parturition(void);  //天狗の分身状態

	void TenguPrePattenrn(void);           //天狗(分身)の状態遷移
	void TenguPreState_Stay(void);         //天狗(分身)待機状態
	void TenguPreState_Thunder(void);      //天狗(分身)雷攻撃状態
	void TenguPreState_Fire(void);         //天狗(分身)の火攻撃状態
	void TenguPreState_Wind(void);         //天狗(分身)の風攻撃状態

	void DeletePre(void);					//分身を消す

	void TenguExp(void);					//本体を爆発させる

	void TextureFlagManager(bool* Tflag);	// 渡したテクスチャフラグをtrueにして、それ以外のテクスチャフラグをfalseにする (本体)
	void TextureFlagManagerPre(bool* Tflag);	// 渡したテクスチャフラグをtrueにして、それ以外のテクスチャフラグをfalseにする (分身)


	int *GetTenguHp(void) { return &m_Tengu.hp; }

	bool *GetTenguThunderHitFlag(void){ return &m_Tengu.thunderHitFlag; }
	//bool *GetTenguThunderHitFlag(void) { return &m_Tengu.ReturnNomalFlag; }
	D3DXVECTOR2 *GetTenguPos(void) { return &m_Tengu.pos; }

	TENGU_KOUZOUTAI *GetTengu(void) { return &m_Tengu; }
	CLOUD *GetTenguCloud(void) { return &m_Cloud; }
	THUNDER *GetTenguThunder(void) { return &m_Thunder; }
	FIRE *GetTenguFire(void) { return m_Fire; }
	WIND *GetTenguWind(void) { return m_Wind; }

	TENGU_KOUZOUTAI *GetTenguPre(void) { return &m_TenguPre; }
	CLOUD *GetTenguCloudPre(void) { return &m_CloudPre; }
	THUNDER *GetTenguThunderPre(void) { return &m_ThunderPre; }
	FIRE *GetTenguFirePre(void) { return m_FirePre; }
	WIND *GetTenguWindPre(void) { return m_WindPre; }

};