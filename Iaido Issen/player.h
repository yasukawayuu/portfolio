#pragma once

#include "main.h"
#include "slash.h"
#include "effect.h"


#define PLAYER_DISP_X (SCREEN_WIDTH/2)			//プレイヤーの表示座標X
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)			//プレイヤーの表示座標Y

//*****************************************************************************
// マクロ定義
//*****************************************************************************


class PLAYER
{
private:
	D3DXVECTOR2 m_pos;							//プレイヤーの位置
	D3DXVECTOR2	m_vel;							//速度ベクトル
	D3DXVECTOR2 m_oldpos;

	float		m_height = 0.0f;						//プレイヤーの高さ
	float		m_size = 0.0f;							//プレイヤーのサイズ
	float       m_gravity = 0.0f;						//プレイヤーの重力
	float		m_crouchingtime = 0.0f;				//しゃがみ時間
	bool		m_crouching = false;					//しゃがんでるかどうか
	bool        m_onGround = false;						//地面にいるか
	bool		m_skychage = false;

	float		m_overheatframe = 0.0f;
	float		m_penaltyframe = 0.0f;
	bool		m_overheatflag = false;

	float		m_movetime = 0.0f; 						//動けるまでの時間
	int			m_muki = 0;							//プレイヤーの向き
	int			m_mukiOld = 0;						//前フレームでプレイヤーが向いていた方向
	int			m_animePtn = 0;						//プレイヤーの動きの切り替え
	int			m_animeReservoirPtn = 0;			//予測するときのアニメーション
	int			m_animeCounter = 0;					//プレイヤーの動きの速さ

	int         m_slashFlag = false;

	int			m_continuity = 0;					//連撃
	float		m_nextcontinuitytime = 0.0f;			//次の二連撃打てる時間
	float		m_continuitytime = 0.0f;				//二連撃が時間ないかどうか
	bool        m_diagonalSlash = false;				//斜めに切った時
	bool		m_predict = false;						//予測影
	bool		m_gopredictpos = false;					//予測先に行けるかどうか
	float		m_shadowspeedY = 0.0f;					//影がY軸を移動するスピード
	float		m_playerY = 0.0f;						// 影が動く予定の場所

	bool		m_unrivaled;
	int			m_unrivaledtime;

	D3DXVECTOR2	m_predictpos;					//予測場所
	int			m_hp = 0;							//プレイヤーの体力
	int			m_live = 0;
	float		m_a = 0.0f;							//透明度
	

	bool		m_use;							//プレイヤーの表示

	int			m_Textureplayer = 0;					//プレイヤーのテクスチャの識別子
	int			m_Texturereservoir = 0;				//プレイヤーの溜めテクスチャの識別子
	int			m_Texturehp = 0;					    //プレイヤーのHPテクスチャの識別子
	int			m_Texturecrouching = 0;				//プレイヤーのしゃがみテクスチャの識別子 
	int			m_Texturelive = 0;
	int			m_Texturehpunder = 0;
	

	bool		m_overheatinit = true;
	bool		m_useRightStick = false;
	bool        m_walkSoundFlag;
	bool        m_landingSoundFlag;
	bool        m_AtSoundFlag;


	float m_AnimeTable[8] =						//プレイヤーのテクスチャu値
	{
		0.0f,
		0.125f,
		0.25f,
		0.375f,
		0.5f,
		0.625f,
		0.75,
		0.875,
	};

	float m_AnimeReservoirTable[5] =			//プレイヤーの溜めテクスチャu値
	{
		0.0f,
		0.2f,
		0.4f,
		0.6f,
		0.8f,
	};

    float m_MukiTable[4] =						//プレイヤーの向きのv値
	{
		0.5f,	//左向き
		0.0f,	//右向き
		0.5f,
		0.0f,
	};

    D3DXVECTOR2 *m_base;							//カメラのベースをゲットした

	SLASH *m_slash;
	EFFECT* m_Effect;

public:
	PLAYER(D3DXVECTOR2 *base, SLASH *slash, EFFECT* Effect) : m_base(base), m_slash(slash),m_Effect(Effect){}	//コンストラクタ(カメラのベースを受け取っている)
	~PLAYER();									//デストラクタ
	void Init(void);							//プレイヤーの初期化処理
	void Uninit(void);							//プレイヤーの終了処理
	void Update(void);							//プレイヤーのアップデート処理
	void Draw(void);							//プレイヤーの描画処理
	D3DXVECTOR2* GetPlayerPos(void);			//プレイヤーの位置を返す
	D3DXVECTOR2 * GetOldPlayerPos(void);
	D3DXVECTOR2* GetPredictPos(void) { return &m_predictpos; }
	int *GetPlayerHp(void) { return &m_hp; }
	bool* GetOnGround(void);					//地面にいるかどうか
	bool* GetGoPredictPos(void);
	bool* GetPlayerUse(void) { return &m_use; }
	int *GetPlayerLive(void) { return &m_live; }
	bool *GetUnrivaled(void) { return &m_unrivaled; }
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

