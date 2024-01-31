/*==============================================================================

   頂点管理 [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "sound1.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define DIVIDE_X 3	//横の分割数
#define DIVIDE_Y 2	//縦の分割数
#define RUN_DIVIDE_X 8	//横の分割数
#define RUN_DIVIDE_Y 2	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)
#define RUN_PATTERN_WIDTH (1.0f / RUN_DIVIDE_X)
#define RUN_PATTERN_HEIGHT (1.0f / RUN_DIVIDE_Y)

#define PLAYER_DISP_X (SCREEN_WIDTH/2)	//プレイヤーの表示座標X
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)	//プレイヤーの表示座標Y

#define SPEED (6.0f)				// 移動スピード

#define ANIMATION_SPEED	6			

#define DECREASE	200	// 空中でチャージをしているときの落下速度 (2 を入れると 1/2 )
#define OVERHEAT_FRAME 60 // 影のX軸が最大値の時にオーバーヒートするまでのフレーム数
#define OVERHEAT_PENALTY_FRAME 120
#define SHADOW_MAX 600


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static int g_Sound_p_at1 = 0;
static int g_Sound_p_at2 = 0;
static int g_Sound_p_la = 0;
static int g_Sound_p_w = 0;



PLAYER::~PLAYER()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
void PLAYER::Init(void)
{
	m_Textureplayer = LoadTexture((char*)"data/TEXTURE/player.png");		//プレイヤー
	m_Texturereservoir = LoadTexture((char*)"data/TEXTURE/reservoir.png");	//プライヤーの溜め
	m_Texturehp = LoadTexture((char*)"data/TEXTURE/zeni.png");				//HP
	m_Texturehpunder = LoadTexture((char*)"data/TEXTURE/zero.png");			//HP(黒)
	m_Texturelive = LoadTexture((char*)"data/TEXTURE/live.png");
	m_Texturecrouching = LoadTexture((char*)"data/TEXTURE/crouching.png"); //しゃがみ状態

	g_Sound_p_at1 = LoadSound((char*)"data/SE/P_At_01.wav");
	g_Sound_p_at2 = LoadSound((char*)"data/SE/P_At_02.wav");
	g_Sound_p_la = LoadSound((char*)"data/SE/P_landing.wav");
	g_Sound_p_w = LoadSound((char*)"data/SE/P_walk.wav");


	//----データの初期化----------------------------------------------------------

	m_pos = D3DXVECTOR2(100.0f, 0.0f);
	m_vel = D3DXVECTOR2(SPEED, SPEED);
	m_muki = 1;
	m_crouchingtime = 0.0f;
	m_animePtn = 0;
	m_animeReservoirPtn = 0;
	m_animeCounter = 0;
	m_movetime = 0.0f;
	m_height = 0.02f;
	m_gravity = 0.0f;
	m_hp = 5;
	m_live = 2;
	m_size = 256.0f;
	m_overheatframe = 0.0f;
	m_overheatflag = false;
	m_onGround = false;
	m_predict = false;
	m_crouching = false;
	m_slashFlag = 0;
	m_diagonalSlash = false;
	m_gopredictpos = true;
	m_walkSoundFlag = false;
	m_landingSoundFlag = false;
	m_AtSoundFlag = false;
	m_use = true;
	m_unrivaled = false;
	m_unrivaledtime = 0;


	
	//----------------------------------------------------------------------------

				
}

//=============================================================================
// 終了処理
//=============================================================================
void PLAYER::Uninit(void)
{
	
}

//=============================================================================
// 更新処理
//=============================================================================
void PLAYER::Update(void)
{
	if (GetKeyboardTrigger(DIK_K))
	{
		m_hp--;
	}
	if (m_use == true)
	{
		m_oldpos = m_pos;
		

		if (m_pos.y > SCREEN_HEIGHT + 500.0f)
		{
			m_hp = 0;
		}

		if (m_unrivaled == true)
		{
			m_unrivaledtime--;
			m_a -= 0.01f;
		}

		if (m_a < 0.5f)
		{
			m_a = 1.0f;
		}

		if (m_unrivaledtime == 0)
		{
			m_unrivaled = false;
			m_unrivaledtime = 300;
			m_a = 1.0f;
		}

		//地面にいなかったら0.5秒しゃがみ時間が増える
		if (m_onGround == false)
		{
			m_crouchingtime = 20.0f;
		}

		if (m_pos.y + m_predictpos.y > SCREEN_HEIGHT || m_pos.x + m_predictpos.x < 0)
		{
			m_gopredictpos = false;
		}


		//----プレイヤーの移動---------------------------------------------------------

			//予測としゃがみが終わるまで動けない
		if (m_predict == false && m_crouching == false && m_overheatflag == false)
		{

			if (GetKeyboardPress(DIK_A) || (GetThumbLeftX(0) < 0))			//A押してるとき
			{
				/*if(m_onGround == true && m_predictpos.x == 0.0f)
				m_Effect->SetRun(D3DXVECTOR2(m_pos.x + 150.0f, m_pos.y + 128.0f));*/

				m_pos.x -= m_vel.x;											//プレイヤーの位置-スピード
				m_muki = 0;	                                                //左向き

				if (m_walkSoundFlag == false)
				{
					PlaySound(g_Sound_p_w, 0);
					m_walkSoundFlag = true;
				}

				if (m_animeCounter > ANIMATION_SPEED)
				{
					//アニメーションパターンを切り替える
					m_animePtn++;											//プレイヤーを動かす
					//最後のアニメーションパターンを表示したらリセットする
					if (m_animePtn >= 8)
						m_animePtn = 3;

					m_animeCounter = 0;
				}
			}
			else if (GetKeyboardPress(DIK_D) || (GetThumbLeftX(0) > 0)) //右移動
			{
				/*if (m_onGround == true && m_predictpos.x == 0.0f)
				m_Effect->SetRun(D3DXVECTOR2(m_pos.x,m_pos.y + 128.0f));*/

				m_pos.x += m_vel.x;
				m_muki = 1;

				if (m_walkSoundFlag == false)
				{
					PlaySound(g_Sound_p_w, 0);
					m_walkSoundFlag = true;
				}

				if (m_animeCounter > ANIMATION_SPEED)
				{
					//アニメーションパターンを切り替える
					m_animePtn++;
					//最後のアニメーションパターンを表示したらリセットする
					if (m_animePtn >= 8)
						m_animePtn = 3;
					m_animeCounter = 0;


				}
			}
			else
			{
				m_Effect->ResetRun();
				m_animePtn = 1;
				m_walkSoundFlag = false;
				StopSound(g_Sound_p_w);
			}

			m_mukiOld = m_muki;
		}


		m_animeCounter++;


		//----プレイヤーがステージにいないの時に落ちる処理---------------------------------

		if (m_onGround == false && m_predict == false)
		{
			//だんだん加速して落ちる
			m_height -= m_gravity;
			//重力加速度の上限値まで
			if (m_gravity < 0.098f)
				m_gravity += 0.01f;

			m_pos.y -= m_height;
		}
		else if (m_onGround == false && m_skychage == true)
		{
			//だんだん加速して落ちる
			m_height -= m_gravity;
			//重力加速度の上限値まで
			if (m_gravity < 5.0f)
				m_gravity += 0.0001f;

			m_pos.y -= m_height / DECREASE;
		}
		else {
			//重力加速度のリセット
			m_height = 0.02f;
			m_gravity = 0;
		}
		//----------------------------------------------------------------------------------

		if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W))
		{
			m_Effect->SetCharge(m_pos);
			m_Effect->ResetRun();
			if (m_AtSoundFlag == false)
			{
				PlaySound(g_Sound_p_at1, 0);
				m_AtSoundFlag = true;
			}
			if (m_predict == false)
				m_muki = 2;
		}
		else if (GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_W))
		{
			m_Effect->SetCharge(m_pos);
			if (m_AtSoundFlag == false)
			{
				PlaySound(g_Sound_p_at1, 0);
				m_AtSoundFlag = true;
			}
			m_Effect->ResetRun();
			if (m_predict == false)
				m_muki = 3;
		}
		else
		{
			m_muki = m_mukiOld;
		}

		//----プレイヤーのチャージと攻撃----------------------------------------------

		//リセットと攻撃//次の二連撃打てる時間が0秒だったら
		if (GetKeyboardRelease(DIK_W) && m_crouching == false && m_nextcontinuitytime == 0.0f ||	// キーボード操作
			m_useRightStick == true && (GetThumbRightY(0) == 0.0f) && (GetThumbRightX(0) == 0.0f) && m_crouching == false && m_nextcontinuitytime == 0.0f)	// PAD操作
		{
			if (m_overheatflag == true) // オーバーヒートした後にスティックを戻したら
			{
				m_useRightStick = false;
			}
			else
			{
				m_overheatinit = true;
				m_skychage = false;

				//予測先障害物や敵とかぶっていなければ
				if (m_gopredictpos == true)
				{
					//連撃のカウントが一以上かつ一秒以内にもう一度連撃したら
					if (m_continuity == 1 && m_continuitytime > 0.0f)
					{
						m_continuity += 1;
					}
					else
					{
						m_continuitytime = 60.0f;
						m_continuity += 1;
					}
					//抜刀のモーション
					m_animeReservoirPtn = 4;

					PlaySound(g_Sound_p_at2, 0);
					//瞬間移動時のエフェクトをセット
					if (m_predictpos > 0)
					{
						m_Effect->SetTeleportation(D3DXVECTOR2(m_pos.x, m_pos.y + 80.0f));
					}
					//予測先に飛ぶ
					m_pos += m_predictpos;
					//攻撃する刀をセットする
					m_slash->SetSlash(m_pos, m_muki);

					//チャージエフェクトをリセット
					m_Effect->SetFlag(1); // チャージをやめる
					m_AtSoundFlag = false;

					m_useRightStick = false;
				}

				//連撃が二回以上になったら
				if (m_continuity == 2)
				{
					//次の二連撃打てるまで2秒間かかる
					m_nextcontinuitytime = 120.0f;
					//連撃のカウントがリセットする
					m_continuity = 0;
				}


				if (m_diagonalSlash == true)
				{
					m_onGround = false;
				}

				m_diagonalSlash = false;

				m_predictpos = D3DXVECTOR2(0.0f, 0.0f);


			}

			m_overheatframe = 0.0f;
		}

		//連撃時間が1秒のカウントダウン
		if (m_continuitytime > 0.0f)
			m_continuitytime -= 1.0f;

		//次の二連撃打てるまでのカウントダウン
		if (m_nextcontinuitytime > 0.0f)
			m_nextcontinuitytime -= 1.0f;

		//地面と当たっていてかつしゃがみ時間0.5秒のカウントダウン
		if (m_onGround == true && m_crouchingtime > 0.0f)
		{
			m_Effect->SetFlag(2); // オーバーヒートは２
			m_crouchingtime -= 1.0f;
			//しゃがんでいる
			if (m_landingSoundFlag == false)
			{
				PlaySound(g_Sound_p_la, 0);
				m_landingSoundFlag = true;
			}
			m_crouching = true;
		}
		else
		{
			//しゃがんでいない
			m_crouching = false;
			m_landingSoundFlag = false;
		}


		//予測動作変動
		if (m_overheatflag == false &&
			((GetKeyboardPress(DIK_W) && m_crouching == false && m_nextcontinuitytime == 0.0f) ||	// キーボード操作
			(GetThumbRightY(0) != 0) && m_crouching == false && m_nextcontinuitytime == 0.0f))	// PAD操作
		{

			if (m_overheatinit == true)
			{
				m_overheatframe = 0;

				m_overheatinit = false;
			}

			if (GetThumbRightY(0) != 0 && m_useRightStick == false)
			{

				m_useRightStick = true;
				m_playerY = 0;
			}

			m_movetime = 200.0f;
			m_predict = true;
			m_skychage = true;

			if (m_predictpos.x <= SHADOW_MAX && m_predictpos.x >= -600.0f && m_predictpos.y >= -SHADOW_MAX)
			{
				if (m_useRightStick == false)
				{
					switch (m_muki)
					{
					case 0:
						m_animeReservoirPtn = 1;
						m_predictpos.x -= 15.0f;
						break;
					case 1:
						m_animeReservoirPtn = 1;
						m_predictpos.x += 15.0f;
						break;
					case 2:
						m_animeReservoirPtn = 0;
						m_predictpos.x -= 15.0f;
						m_predictpos.y -= 15.0f;
						m_diagonalSlash = true;
						break;
					case 3:
						m_animeReservoirPtn = 0;
						m_predictpos.x += 15.0f;
						m_predictpos.y -= 15.0f;
						m_diagonalSlash = true;
						break;
					}
				}

				// PAD用

				if (m_useRightStick == true)
				{
					m_Effect->SetCharge(m_pos);
					m_Effect->ResetRun();
					// 影のXが最大値ではない時
					if (m_muki == 0)
					{
						m_predictpos.x -= 15.0f; // 左
					}
					else if (m_muki == 1)
					{
						m_predictpos.x += 15.0f; // 右
					}
				}
			}
			else // 影のX座標がMAXの時
			{
				if (m_overheatframe >= OVERHEAT_FRAME)
				{
					m_Effect->SetFlag(2);
					m_overheatflag = true;
				}
				m_overheatframe++;
			}
			// 影のYが最大値ではない時
			m_playerY -= GetThumbRightY(0) * 15.0f;
			// チャージ中のUV値を設定
			switch (m_muki)
			{
			case 0:
				if (GetThumbRightY(0) >= 0.5f)
				{
					m_animeReservoirPtn = 0;

					break;
				}
				else if (GetThumbRightY(0) < 0.5f && GetThumbRightY(0) > -0.5f)
				{
					m_animeReservoirPtn = 1;

					break;
				}
				else
				{
					m_animeReservoirPtn = 3;

					break;
				}

			case 1:
				if (GetThumbRightY(0) >= 0.5f)
				{
					m_animeReservoirPtn = 0;

					break;
				}
				else if (GetThumbRightY(0) < 0.5f && GetThumbRightY(0) > -0.5f)
				{
					m_animeReservoirPtn = 1;

					break;
				}
				else
				{
					m_animeReservoirPtn = 3;

					break;
				}
			}

			if (m_playerY <= SHADOW_MAX && m_playerY >= -SHADOW_MAX)
			{
				m_predictpos.y = m_playerY;
			}
		}

		if (m_overheatflag == true)
		{
			if (m_penaltyframe >= OVERHEAT_PENALTY_FRAME)
			{
				m_Effect->SetFlag(1);
				m_overheatflag = false;
				m_penaltyframe = 0;
				m_predictpos = D3DXVECTOR2(0.0f, 0.0f);
			}
			else
			{
				m_penaltyframe++;
			}
		}

		else if (m_overheatflag == true)
		{
			m_predictpos = D3DXVECTOR2(0.0f, 0.0f);
		}

		if (m_movetime == 0.0f)
		{
			m_predict = false;
		}
		else
		{
			m_movetime -= 10.0f;
		}
		//----------------------------------------------------------------------------


		if (m_hp < 1)
		{
			m_hp = 5;
			m_live -= 1;
			if (m_pos.x > 0 && m_pos.x < SCREEN_WIDTH)
			{
				m_pos = D3DXVECTOR2(100.0f, 0.0f);
			}
			if (m_pos.x > SCREEN_WIDTH && m_pos.x < SCREEN_WIDTH * 2)
			{
				m_pos = D3DXVECTOR2(SCREEN_WIDTH + 100.0f, 0.0f);
			}
			if (m_pos.x > SCREEN_WIDTH * 2 && m_pos.x < SCREEN_WIDTH * 3)
			{
				m_pos = D3DXVECTOR2(SCREEN_WIDTH * 2 + 100.0f, 0.0f);
			}
			if (m_pos.x > SCREEN_WIDTH * 3 && m_pos.x < SCREEN_WIDTH * 4)
			{
				m_pos = D3DXVECTOR2(SCREEN_WIDTH * 3 + 100.0f, 0.0f);
			}
		}

		if (m_live < 1)
		{
			m_use = false;
		}

		if (m_pos.x < 49.0f)
			m_pos = m_oldpos;
	}
}


//=============================================================================
// 描画処理
//=============================================================================
void PLAYER::Draw(void)
{
//----プレイヤーのHPの描写--------------------------------------------------
	// HP(下　黒)
	for (int i = 0; i < 5; i++)
	{
		DrawSpriteLeftTop(m_Texturehpunder,
			0.0f + (102.0f * i),
			0.0f,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}


// HP(上　フル)
	for (int i = 0; i < m_hp; i++)
	{
		DrawSpriteLeftTop(m_Texturehp,
			0.0f + (102.0f * i),
			0.0f,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}

	for (int i = 0; i < m_live; i++)
	{
		DrawSpriteLeftTop(m_Texturelive,
			0.0f + (102.0f * i),
			102.0f,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}

//----------------------------------------------------------------------------
	
	if (m_use == true)
	{

		//----プレイヤーの描画--------------------------------------------------------
			//予測もしゃがんでもいなかったら
		if (m_predict == false && m_crouching == false && m_overheatflag == false)
		{
			DrawSpriteColor(m_Textureplayer,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y,
				192.0f, m_size,
				m_AnimeTable[m_animePtn],
				m_MukiTable[m_muki],
				RUN_PATTERN_WIDTH,
				RUN_PATTERN_HEIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));
		}

		//地面と当たっていてかつしゃがみ時間内だったら
		if (m_onGround == true && m_crouchingtime > 0.0f || m_overheatflag == true)
		{
			DrawSpriteColor(m_Texturecrouching,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y + 30.0f,
				192.0f, m_size,
				0.333f,
				m_MukiTable[m_muki],
				PATTERN_WIDTH,
				PATTERN_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));
		}

		//プレイヤーの予測行動の描画
		if (m_predict == true && m_overheatflag == false)
		{

			DrawSpriteColor(m_Texturereservoir,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y,
				192.0f, m_size,
				m_AnimeReservoirTable[m_animeReservoirPtn],
				m_MukiTable[m_muki],
				0.2f,
				0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));

			DrawSpriteColor(m_Texturereservoir,
				m_base->x + m_pos.x + m_predictpos.x,
				m_base->y + m_pos.y + m_predictpos.y,
				192.0f, m_size,
				m_AnimeReservoirTable[m_animeReservoirPtn],
				m_MukiTable[m_muki],
				0.2f,
				0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8));
		}

		//----------------------------------------------------------------------------
	}
}

D3DXVECTOR2 * PLAYER::GetPlayerPos(void)
{
	return &m_pos;
}

D3DXVECTOR2 * PLAYER::GetOldPlayerPos(void)
{
	return &m_oldpos;
}

bool * PLAYER::GetOnGround(void)
{
	return &m_onGround;
}

bool * PLAYER::GetGoPredictPos(void)
{
	return &m_gopredictpos;
}










