#include "tengu.h"
#include "sound1.h"
#include "stagemanager.h"

static int	g_BGM_tengu = 0;		// BGM識別子

static int g_Sound_t_at1 = 0;
static int g_Sound_t_at2 = 0;
static int g_Sound_t_at3 = 0;
static int g_Sound_t_at4 = 0;
static int g_Sound_t_at5 = 0;
static int g_Sound_t_at6 = 0;
static int g_Sound_t_at7 = 0;
static int g_Sound_t_at8 = 0;


void TENGU::Init(void)
{
	//タイトル画面用テクスチャの読み込み
	m_TextureTenguHp0 = LoadTexture((char*)"data/TEXTURE/tengu/kuro.png");
	m_TextureTenguHp1 = LoadTexture((char*)"data/TEXTURE/tengu/tengutairyoku.png");
	m_TextureTenguNomal = LoadTexture((char*)"data/TEXTURE/tengu/taiki.png");				//天狗(待機)
	m_TextureTenguThunderAtk = LoadTexture((char*)"data/TEXTURE/tengu/thunder_atk.png");	//天狗(雷攻撃)
	m_TextureTenguThunder = LoadTexture((char*)"data/TEXTURE/tengu/biribiri.png");			//天狗(雷被弾)
	m_TextureTenguFall = LoadTexture((char*)"data/TEXTURE/tengu/rakka.png");				//天狗(落下)
	m_TextureTenguDown = LoadTexture((char*)"data/TEXTURE/tengu/dawn.png");					//天狗(ダウン)
	m_TextureTenguFire = LoadTexture((char*)"data/TEXTURE/tengu/fire_atk.png");				//天狗(炎攻撃)
	m_TextureTenguWind = LoadTexture((char*)"data/TEXTURE/tengu/wind_atk.png");				//天狗(風攻撃)
	m_TextureTenguHit = LoadTexture((char*)"data/TEXTURE/tengu/hidan.png");					//天狗(被弾)
	m_TextureCloud = LoadTexture((char*)"data/TEXTURE/tengu/cloud1.png");					//雲
	m_TextureThunder = LoadTexture((char*)"data/TEXTURE/tengu/kaminari1.png");				//雷
	m_TextureFire = LoadTexture((char*)"data/TEXTURE/tengu/fire1.png");						//火
	m_TextureWind = LoadTexture((char*)"data/TEXTURE/tengu/strom1.png");					//風
	m_TextureExp = LoadTexture((char*)"data/TEXTURE/tengu/Explosion1.png");					//爆発

	g_Sound_t_at1 = LoadSound((char*)"data/SE/神々しい神楽鈴の音.wav");
	g_Sound_t_at2 = LoadSound((char*)"data/SE/炎ボッ.wav");
	g_Sound_t_at3 = LoadSound((char*)"data/SE/炎メラメラ.wav");
	g_Sound_t_at4 = LoadSound((char*)"data/SE/雷ゴロゴロ.wav");
	g_Sound_t_at5 = LoadSound((char*)"data/SE/雷ドーン.wav");
	g_Sound_t_at6 = LoadSound((char*)"data/SE/竜巻.wav");
	g_Sound_t_at7 = LoadSound((char*)"data/SE/雷ゴロゴロ2.wav");
	g_Sound_t_at8 = LoadSound((char*)"data/SE/雷ドーン.wav");
	

	g_BGM_tengu = LoadSound((char*)"data/BGM/vs天狗.wav");

	
	
	//天狗の設定
	m_Tengu.pos = D3DXVECTOR2(400, 200);
	m_Tengu.use = true;
	m_Tengu.hp = 3;
	m_Tengu.stateteng = TENGU_STATE_STAY;
	m_Tengu.move = true;
	m_Tengu.nomalFlag = true;
	m_Tengu.thunderAtkFrag = false;
	m_Tengu.thunderHitFlag = false;
	m_Tengu.thunderDownFrame = 0;
	m_Tengu.fallFlag = false;
	m_Tengu.downFlag = false;
	m_Tengu.atkFlag = false;
	m_Tengu.hitFlag = false;
	m_Tengu.texHitFlag = false;
	m_Tengu.fireFlag = false;
	m_Tengu.hitFrame = 0;
	m_Tengu.ReturnNomalFlag = false;
	m_Tengu.windFlag = false;
	m_Tengu.animeCounter = 0;
	m_Tengu.animePtn = 0.0f;

	m_TenguBGMSoundFlag = false;

	//雲の設定
	m_Cloud.use = false;
	m_Cloud.anmPtn = 0;
	m_Cloud.anmFrame = 0;

	//雷の設定
	m_Thunder.use = false;

	//火の設定
	for (int i = 0; i < 1; i++)
	{
		m_Fire[i].use = false;
		m_Fire[i].speed = FIRE_SPEED;
		m_Fire[i].onGround = false;
	}

	//風の設定
	for (int i = 0; i < 1; i++)
	{
		m_Wind[i].use = false;
		m_Wind[i].speed.x = frand() * 10.0 - 5.0f;
		m_Wind[i].speed.y = -3.0f;
	}

	

	//天狗の分身の設定
	m_TenguPre.pos = D3DXVECTOR2(1000, 200);
	m_TenguPre.use = false;
	m_Tengu.vel = 5.0f;
	m_TenguPre.stateteng = TENGU_STATE_NONE;
	m_TenguPre.nomalFlag = true;
	m_Tengu.thunderAtkFrag = false;
	m_TenguPre.fireFlag = false;
	m_TenguPre.windFlag = false;
	m_TenguPre.animeCounter = 0;
	m_TenguPre.animePtn = 0.0f;

	//雲分身の設定
	m_CloudPre.use = false;

	//雷分身の設定
	m_ThunderPre.use = false;

	//火分身の設定
	for (int i = 0; i < 1; i++)
	{
		m_FirePre[i].use = false;
		m_FirePre[i].speed = FIRE_SPEED;
		m_FirePre[i].onGround = false;
	}

	//風分身の設定
	for (int i = 0; i < 1; i++)
	{
		m_WindPre[i].use = false;
		m_WindPre[i].speed.x = frand() * 10.0 - 5.0f;
		m_WindPre[i].speed.y = -3.0f;
	}

	m_Exp.use = false;
	m_Exp.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Exp.anmFrame = 0;
	m_Exp.anmPtn = 0.0f;

}

void TENGU::Uninit(void)
{
	m_TenguBGMSoundFlag = false;
	StopSound(g_BGM_tengu);
}

void TENGU::Update(void)
{
	//天狗の状態遷移
	TenguPattenrn();

	TenguPrePattenrn();

	if (m_TenguBGMSoundFlag == false)
	{   
		StopSoundAll();
		//255(-1)をループ指定すると無限ループ
		PlaySound(g_BGM_tengu, -1);
		SetVolume(g_BGM_tengu, 0.5);
		m_TenguBGMSoundFlag = true;
	}

	if (m_Wind[0].use == true)//竜巻があるとき音が鳴る
	{
		if (m_TenguAtSoundFlag1 == false)
		{
			PlaySound(g_Sound_t_at6, -1);
			m_TenguAtSoundFlag1 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag1 = false;
		StopSound(g_Sound_t_at6);
	}


	if (m_Fire[0].use == true)//火があるとき音が鳴る
	{
		if (m_TenguAtSoundFlag2 == false)
		{
			PlaySound(g_Sound_t_at3, -1);
			m_TenguAtSoundFlag2 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag2 = false;
		StopSound(g_Sound_t_at3);
	}

	if (m_Cloud.use == true )//雲があるとき音が鳴る
	{
		if (m_TenguAtSoundFlag3 == false)
		{
			PlaySound(g_Sound_t_at4, -1);
			m_TenguAtSoundFlag3 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag3 = false;
		StopSound(g_Sound_t_at4);
	}

	if (m_Thunder.use == true)//雷があるとき音が鳴る
	{
		if (m_TenguAtSoundFlag4 == false)
		{
			PlaySound(g_Sound_t_at5, 0);
			m_TenguAtSoundFlag4 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag4 = false;

	}

	if (m_CloudPre.use == true)//分身雲があるとき音が鳴る
	{
		if (m_TenguAtSoundFlag5 == false)
		{
			PlaySound(g_Sound_t_at7, -1);
			m_TenguAtSoundFlag5 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag5 = false;
		StopSound(g_Sound_t_at7);
	}

	if (m_ThunderPre.use == true)//分身雷があるとき音が鳴る
	{
		if (m_TenguAtSoundFlag6 == false)
		{
			PlaySound(g_Sound_t_at5, 0);
			m_TenguAtSoundFlag6 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag6 = false;

	}

	// アニメーションの更新
	if (m_Tengu.animeCounter > ANIMATION_COUNT)
	{
		m_Tengu.animePtn++;

		if (m_Tengu.animePtn >= 25)
			m_Tengu.animePtn = 0;

		m_Tengu.animeCounter = 0;
	}
	m_Tengu.animeCounter++;

	if (m_Tengu.hp <= 0)
	{
		TenguExp();
		m_Tengu.use = false;
		m_TenguPre.use = false;
	}
}

void TENGU::Draw(void)
{
	
	//天狗の描画処理
	if (m_Tengu.use == true)
	{
		// 待機
		if (m_Tengu.nomalFlag == true)
		{
			DrawSprite(m_TextureTenguNomal,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// 雷攻撃
		else if (m_Tengu.thunderAtkFrag == true)
		{
			
			DrawSprite(m_TextureTenguThunderAtk,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// 感電中
		else if (m_Tengu.thunderHitFlag == true)
		{
			DrawSprite(m_TextureTenguThunder,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// 落下中
		else if (m_Tengu.fallFlag == true)
		{
			DrawSprite(m_TextureTenguFall,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
		}
		// ダウン
		else if (m_Tengu.downFlag == true)
		{
			DrawSprite(m_TextureTenguDown,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
		}
		// 炎攻撃
		else if (m_Tengu.fireFlag == true)
		{
			DrawSprite(m_TextureTenguFire,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 3, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// 風攻撃
		else if (m_Tengu.windFlag == true)
		{
			DrawSprite(m_TextureTenguWind,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f);
		}
		// 被弾
		else if (m_Tengu.texHitFlag == true)
		{
			DrawSprite(m_TextureTenguHit,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				1.0f / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
		}


		//雷攻撃の描画
		if (m_Cloud.use == true)
		{
			if (m_Thunder.use == true)
			{
				//雷の描画
				DrawSprite(m_TextureThunder, m_base->x + m_Thunder.pos.x, m_base->y + (m_Thunder.pos.y + 512), 600.0f, 1024.0f,
					m_Tengu.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
			}

			//雲の描画
			DrawSprite(m_TextureCloud, m_base->x + m_Cloud.pos.x, m_base->y + m_Cloud.pos.y, 192.0f, 256.0f,
				m_Cloud.anmPtn / 2.0f, 0.0f, 1.0f / 2.0f, 1.0f);
		}
		//火攻撃の描画
		for (int i = 0; i < 1; i++)
		{
			if (m_Fire[i].use == true)
			{
				//火の描画
				DrawSprite(m_TextureFire, m_base->x + m_Fire[i].pos.x, m_base->y + m_Fire[i].pos.y, 400.0f, 256.0f,
					m_Tengu.animePtn / 5, ((int)m_Tengu.animePtn) % 5 / 5.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f);
			}
		}

		//風の攻撃の描画
		for (int i = 0; i < 1; i++)
		{
			if (m_Wind[i].use == true)
			{
				//風の描画
				DrawSprite(m_TextureWind, m_base->x + m_Wind[i].pos.x, m_base->y + m_Wind[i].pos.y, 250.0f, 310.0f,
					m_Tengu.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f);
				
			}
			
		}
	}

	//分身天狗の描画
	if (m_TenguPre.use == true)
	{
		// 待機
		if (m_TenguPre.nomalFlag == true)
		{
			DrawSpriteColor(m_TextureTenguNomal,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// 雷攻撃
		else if (m_TenguPre.thunderAtkFrag == true)
		{
			DrawSpriteColor(m_TextureTenguThunderAtk,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// 感電中
		else if (m_TenguPre.thunderHitFlag == true)
		{
			DrawSpriteColor(m_TextureTenguThunder,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// 炎攻撃
		else if (m_TenguPre.fireFlag == true)
		{
			DrawSpriteColor(m_TextureTenguFire,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / 3, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// 風攻撃
		else if (m_TenguPre.windFlag == true)
		{
			DrawSpriteColor(m_TextureTenguWind,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				250.0f, 310.0f,
				m_TenguPre.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}




		//雷攻撃の描画
		if (m_CloudPre.use == true)
		{
			if (m_ThunderPre.use == true)
			{
				//雷の描画
				DrawSpriteColor(m_TextureThunder, m_base->x + m_ThunderPre.pos.x, m_base->y + (m_ThunderPre.pos.y + 512), 600.0f, 1024.0f,
					m_TenguPre.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f,
					D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
			}

			//雲の描画
			DrawSpriteColor(m_TextureCloud, m_base->x + m_CloudPre.pos.x, m_base->y + m_CloudPre.pos.y, 192.0f, 256.0f,
				m_CloudPre.anmPtn / 2.0f, 0.0f, 1.0f / 2.0f, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		//火攻撃の描画
		for (int i = 0; i < 1; i++)
		{
			if (m_FirePre[i].use == true)
			{
				//火の描画
				DrawSpriteColor(m_TextureFire, m_base->x + m_FirePre[i].pos.x, m_base->y + m_FirePre[i].pos.y, 400.0f, 256.0f,
					m_TenguPre.animePtn / 5, ((int)m_TenguPre.animePtn) % 5 / 5.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f,
					D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
			}
		}

		//風の攻撃の描画
		for (int i = 0; i < 1; i++)
		{
			if (m_WindPre[i].use == true)
			{
				//風の描画
				DrawSpriteColor(m_TextureWind, m_base->x + m_WindPre[i].pos.x, m_base->y + m_WindPre[i].pos.y, 250.0f, 310.0f,
					m_TenguPre.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f,
					D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
			}
		}

	}
	// 爆発の描画
	if (m_Exp.use == true)
	{
		DrawSprite(m_TextureExp, m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y + 50.0f, 800.0f, 800.0f,
			m_Exp.anmPtn / 5, ((int)m_Exp.anmPtn) % 5 / 6.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f);
	}

	//HP(下)の描画
	for (int i = 3; i >= 1; i--)
	{
		DrawSprite(m_TextureTenguHp0, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	//HP(上)の描画
	for (int i = m_Tengu.hp; i >= 1; i--)
	{
		DrawSprite(m_TextureTenguHp1, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
}


//----天狗のパターン遷移---------------------------------
void TENGU::TenguPattenrn(void)
{

	if (m_Tengu.use == true)
	{
		//敵の時間を進める
		m_Tengu.frame++;

		//敵の状態によって動作を切り替える
		switch (m_Tengu.stateteng)
		{
		case TENGU_STATE_STAY:   //待機状態
			TenguState_Stay();
			break;
		case TENGU_STATE_THUNDER1://雷状態
			TenguState_Thunder();
			break;
		case TENGU_STATE_THUNDER2://雷状態
			TenguState_Thunder();
			break;
		case TENGU_STATE_THUNDER3://雷状態
			TenguState_Thunder();
			break;
		case TENGU_STATE_FIRE:   //火攻撃状態
			TenguState_Fire();
			break;
		case TENGU_STATE_WIND://風攻撃状態
			TenguState_Wind();
			break;
		case TENGU_STATE_PARTURITION://分身状態
			TenguState_Parturition();
			break;
		}

	}
}
//----------------------------------------------------------------------------

//----天狗の待機処理---------------------------------
void TENGU::TenguState_Stay(void)
{
	if (m_Tengu.move == true)
	{
		TextureFlagManager(&m_Tengu.nomalFlag);

		if ((m_Tengu.pos.x <= 0) || (m_Tengu.pos.x >= SCREEN_WIDTH))
			m_Tengu.vel *= -1.0f;

		m_Tengu.pos.x += m_Tengu.vel;

		if (m_TenguPre.use == true)
		{
			r = (rand() % 5) + 2;
		}
		else
		{
			r = (rand() % 6) + 2;
		}

		//ランダムで次の状態を入れる
		if (m_Tengu.frame >= 180)
		{
			m_Tengu.frame = 0;
			m_Tengu.stateteng = r;
		}
	}

	else // 天狗が動けない時
	{
		// 痺れている
		if (m_Tengu.thunderHitFlag == true)
		{
			if (m_Tengu.thunderDownFrame >= THUNDER_DOWN_FRAME)
			{
				m_Tengu.thunderDownFrame = 0;
				TextureFlagManager(&m_Tengu.fallFlag);
			}
			m_Tengu.thunderDownFrame++;
		}
		// 落ちている
		if (m_Tengu.fallFlag == true)
		{
			m_Cloud.use = false;
			m_Thunder.use = false;

			if (m_Tengu.pos.y <= GROUND_POS)
				m_Tengu.pos.y += 5.0f;
			// 地面まで落ちた
			if (m_Tengu.pos.y >= GROUND_POS)
			{
				m_Tengu.pos.y = GROUND_POS;
				TextureFlagManager(&m_Tengu.downFlag);
				m_Tengu.atkFlag = true;
			}
		}
		// 地面まで落ちた後
		if (m_Tengu.downFlag == true)
		{
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//Collision_HitTenguPlayerAtk();	// プレイヤーからの攻撃を受けたか
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			if (m_Tengu.downFrame >= DOWN_FRAME)
			{
				m_Tengu.ReturnNomalFlag = true;
				m_Tengu.downFlag = false;
				m_Tengu.downFrame = 0;
			}
			m_Tengu.downFrame++;
		}
		// 攻撃を受ける
		if (m_Tengu.hitFlag == true)
		{
			m_Tengu.downFrame = 0;

			m_Tengu.atkFlag = false;
			TextureFlagManager(&m_Tengu.texHitFlag);

			if (m_Tengu.hitFrame >= HIT_FRAME)
			{
				m_Tengu.ReturnNomalFlag = true;
				m_Tengu.hitFlag = false;
				m_Tengu.hitFrame = 0;
			}
			m_Tengu.hitFrame++;
		}
		// 元の場所へ戻る
		if (m_Tengu.ReturnNomalFlag == true)
		{
			TextureFlagManager(&m_Tengu.nomalFlag);

			m_Tengu.pos.y -= 10.0f;
			if (m_Tengu.pos.y <= 200.0f)
			{
				m_Tengu.pos.y = 200.0f;
				m_Tengu.ReturnNomalFlag = false;
				m_Thunder.pos = D3DXVECTOR2(-100.0f, -100.0f);
				m_Tengu.move = true;
			}
		}
	}
}
//----------------------------------------------------------------------------

//----天狗の雷攻撃処理---------------------------------
void TENGU::TenguState_Thunder(void)
{
	m_Cloud.frame++;

	if (m_Cloud.frame >= THUNDER_FRAME)
	{
		m_Thunder.frame++;
		//雲を可視化
		m_Thunder.use = true;
		//雷の座標を設定
		m_Thunder.pos = m_Cloud.pos;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//雷との当たり判定をとる
		//Collision_Thunder();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		

		if (m_Thunder.frame >= 60)
		{
			//初期化
			m_Thunder.frame = 0;
			m_Cloud.frame = 0;
			m_Tengu.frame = 0;
			m_Cloud.anmPtn = 0;
			m_Cloud.anmFrame = 0;
			m_Thunder.pos = D3DXVECTOR2(-100.0f, -100.0f); // 画面内に透明な雷を残さない
			m_Cloud.use = false;
			m_Thunder.use = false;
			//待機状態に移行
			m_Tengu.stateteng = TENGU_STATE_STAY;

		}

	}
	else
	{
		//プレイヤーに追従
		TextureFlagManager(&m_Tengu.thunderAtkFrag);

		if(m_Cloud.frame <= THUNDER_FRAME - 20)
		m_Cloud.pos.x = m_playerpos->x;

		m_Cloud.use = true;
		if (m_Cloud.anmFrame >= 20)
		{
			m_Cloud.anmPtn++;
			m_Cloud.anmFrame = 0;
		}
		m_Cloud.anmFrame++;
	}
}
//----------------------------------------------------------------------------

//----天狗の火攻撃処理---------------------------------
void TENGU::TenguState_Fire(void)
{
	TextureFlagManager(&m_Tengu.fireFlag);

	for (int i = 0; i < 1; i++)
	{
		if (m_Fire[i].use == false)
		{
			//火を可視化
			m_Fire[i].use = true;
			m_Fire[i].pos = m_Tengu.pos;
			m_rand[i] = rand() % SCREEN_WIDTH;
			//火の移動する予測地点を設定
			m_Fire[i].prepos = D3DXVECTOR2(m_rand[i], GROUNDLINE);
		}

		m_Fire[i].vDist = m_Fire[i].prepos - m_Fire[i].pos;
		m_Fire[i].len = D3DXVec2Length(&m_Fire[i].vDist);

		if (m_Fire[i].len >= 2)
		{
			//天狗の火が向かうベクトルを作る
			m_Fire[i].dir = m_Fire[i].prepos - m_Fire[i].pos;
			//ベクトルを正規化する
			D3DXVec2Normalize(&m_Fire[i].dir, &m_Fire[i].dir);

			m_Fire[i].pos += m_Fire[i].dir * m_Fire[i].speed;

			m_Fire[i].frame++;

		}
		else
		{
			if (m_Fire[i].frame != 0)
			{
				m_Fire[i].frame = 0;
				m_Fire[i].onGround = true;
			}
			//全部地面に付いていたら
			if (m_Fire[0].onGround == true)
			{
				m_Tengu.frame = 0;
				//待機状態に移行
				m_Tengu.stateteng = TENGU_STATE_STAY;
			}
		}

	}
}
//----------------------------------------------------------------------------

//----天狗の風攻撃の設定---------------------------------
void TENGU::TenguState_Wind(void)
{
	TextureFlagManager(&m_Tengu.windFlag);

	if (m_Wind[0].use == false)
	{
		m_Wind[0].pos = D3DXVECTOR2(frand() * SCREEN_WIDTH, GROUNDLINE);
		//m_Wind[1].pos = D3DXVECTOR2((frand() * (SCREEN_WIDTH / 2) + SCREEN_WIDTH / 2) - 1, GROUNDLINE);
		m_Wind[0].use = true;
		//m_Wind[1].use = true;
	}
	for (int i = 0; i < 1; i++)
	{

		m_Wind[i].frame++;

		if (m_Wind[i].frame >= 30)
		{
			m_Wind[i].speed.x = frand() * 10.0 - 5.0f;
			m_Wind[i].frame = 0;
		}

		m_Wind[i].pos.y += m_Wind[i].speed.y;

		m_Wind[i].pos.x += m_Wind[i].speed.x;

		if (m_Wind[i].pos.x < 0 || m_Wind[i].pos.x > SCREEN_WIDTH || m_Wind[i].pos.y < 0)
		{
			m_Wind[i].use = false;
		}

		if (m_Wind[0].use == false)
		{
			m_Tengu.frame = 0;
			m_Tengu.stateteng = TENGU_STATE_STAY;
		}

	}
}
//----------------------------------------------------------------------------

//----天狗の分身処理処理---------------------------------
void TENGU::TenguState_Parturition(void)
{
	m_TenguPre.pos = D3DXVECTOR2(1000, 200);
	m_TenguPre.use = true;
	m_TenguPre.move = true;

	m_Tengu.stateteng = TENGU_STATE_STAY;
	m_TenguPre.stateteng = TENGU_STATE_STAY;
}
//----------------------------------------------------------------------------


//----天狗(分身)のパターン遷移---------------------------------
void TENGU::TenguPrePattenrn(void)
{
	if (m_TenguPre.use == true)
	{
		//敵の時間を進める
		m_TenguPre.frame++;

		//敵の状態によって動作を切り替える
		switch (m_TenguPre.stateteng)
		{
		case TENGU_STATE_STAY:   //待機状態
			TenguPreState_Stay();
			break;
		case TENGU_STATE_THUNDER1://雷状態
			TenguPreState_Thunder();
			break;
		case TENGU_STATE_THUNDER2://雷状態
			TenguPreState_Thunder();
			break;
		case TENGU_STATE_THUNDER3://雷状態
			TenguPreState_Thunder();
			break;
		case TENGU_STATE_FIRE:   //火攻撃状態
			TenguPreState_Fire();
			break;
		case TENGU_STATE_WIND://風攻撃状態
			TenguPreState_Wind();
			break;
		}

		// アニメーションの更新
		if (m_TenguPre.animeCounter > ANIMATION_COUNT)
		{
			m_TenguPre.animePtn++;

			if (m_TenguPre.animePtn >= 25)
				m_TenguPre.animePtn = 0;

			m_TenguPre.animeCounter = 0;
		}
		m_TenguPre.animeCounter++;

	}
}
//----------------------------------------------------------------------------

//----天狗(分身)の待機処理---------------------------------
void TENGU::TenguPreState_Stay(void)
{
	if (m_TenguPre.move == true)
	{
		if (m_TenguPre.use == true)
		{
			TextureFlagManagerPre(&m_TenguPre.nomalFlag);
			rPre = (rand() % 3) + 2;
		}
		//ランダムで次の状態を入れる
		if (m_TenguPre.frame >= 360)
		{
			m_TenguPre.frame = 0;
			m_TenguPre.stateteng = rPre;
		}
	}
	else
	{
		// 痺れている
		if (m_TenguPre.thunderHitFlag == true)
		{
			if (m_TenguPre.thunderDownFrame >= THUNDER_DOWN_FRAME)
			{
				m_TenguPre.thunderDownFrame = 0;
				DeletePre(); // 分身を消す
			}
			m_TenguPre.thunderDownFrame++;
		}
	}

}
//----------------------------------------------------------------------------

//----天狗(分身)の雷攻撃処理---------------------------------
void TENGU::TenguPreState_Thunder(void)
{
	m_CloudPre.frame++;

	if (m_CloudPre.frame >= THUNDER_FRAME)
	{
		m_ThunderPre.frame++;
		//雲を可視化
		m_ThunderPre.use = true;
		//雷の座標を設定
		m_ThunderPre.pos = m_CloudPre.pos;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//雷との当たり判定をとる
		//Collision_Thunder();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		if (m_ThunderPre.frame >= 60)
		{
			//初期化
			m_ThunderPre.frame = 0;
			m_CloudPre.frame = 0;
			m_TenguPre.frame = 0;
			m_ThunderPre.pos = D3DXVECTOR2(-100.0f, -100.0f); // 画面内に透明な雷を残さない
			m_CloudPre.use = false;
			m_ThunderPre.use = false;
			//待機状態に移行
			m_TenguPre.stateteng = TENGU_STATE_STAY;
		}

	}
	else
	{
		TextureFlagManagerPre(&m_TenguPre.thunderAtkFrag);
		//プレイヤーに追従
		if (m_CloudPre.frame <= THUNDER_FRAME - 20)
			m_CloudPre.pos.x = m_playerpos->x;
	
		m_CloudPre.use = true;

		if (m_CloudPre.anmFrame >= 20)
		{
			m_CloudPre.anmPtn++;
			m_CloudPre.anmFrame = 0;
		}
		m_CloudPre.anmFrame++;
	}

}
//----------------------------------------------------------------------------

//----天狗(分身)の火攻撃処理---------------------------------
void TENGU::TenguPreState_Fire(void)
{
	TextureFlagManagerPre(&m_TenguPre.fireFlag);
	for (int i = 0; i < 1; i++)
	{
		if (m_FirePre[i].use == false)
		{
			//火を可視化
			m_FirePre[i].use = true;
			m_FirePre[i].pos = m_TenguPre.pos;
			m_randPre[i] = rand() % SCREEN_WIDTH;
			//火の移動する予測地点を設定
			m_FirePre[i].prepos = D3DXVECTOR2(m_randPre[i], GROUNDLINE);
		}

		m_FirePre[i].vDist = m_FirePre[i].prepos - m_FirePre[i].pos;
		m_FirePre[i].len = D3DXVec2Length(&m_FirePre[i].vDist);

		if (m_FirePre[i].len >= 2)
		{
			//天狗の火が向かうベクトルを作る
			m_FirePre[i].dir = m_FirePre[i].prepos - m_FirePre[i].pos;
			//ベクトルを正規化する
			D3DXVec2Normalize(&m_FirePre[i].dir, &m_FirePre[i].dir);

			m_FirePre[i].pos += m_FirePre[i].dir * m_FirePre[i].speed;

			m_FirePre[i].frame++;

		}
		else
		{
			if (m_FirePre[i].frame != 0)
			{
				m_FirePre[i].frame = 0;
				m_FirePre[i].onGround = true;
			}
			//全部地面に付いていたら
			if (m_FirePre[0].onGround == true)
			{

				m_TenguPre.frame = 0;
				//待機状態に移行
				m_TenguPre.stateteng = TENGU_STATE_STAY;
			}
		}

	}
}
//----------------------------------------------------------------------------

//----天狗(分身)の風攻撃の設定---------------------------------
void TENGU::TenguPreState_Wind(void)
{
	TextureFlagManagerPre(&m_TenguPre.windFlag);
	if (m_WindPre[0].use == false && m_WindPre[1].use == false)
	{
		m_WindPre[0].pos = D3DXVECTOR2(frand() * SCREEN_WIDTH, GROUNDLINE);
		//m_WindPre[1].pos = D3DXVECTOR2(frand() * (SCREEN_WIDTH / 2) + SCREEN_WIDTH / 2, GROUNDLINE);
		m_WindPre[0].use = true;
		//m_WindPre[1].use = true;
	}
	for (int i = 0; i < 1; i++)
	{

		m_WindPre[i].frame++;

		if (m_WindPre[i].frame >= 30)
		{
			m_WindPre[i].speed.x = frand() * 10.0 - 5.0f;
			m_WindPre[i].frame = 0;
		}

		m_WindPre[i].pos.y += m_WindPre[i].speed.y;

		m_WindPre[i].pos.x += m_WindPre[i].speed.x;

		if (m_WindPre[i].pos.x < 0 || m_WindPre[i].pos.x > SCREEN_WIDTH || m_WindPre[i].pos.y < 0)
		{
			m_WindPre[i].use = false;
		}

		if (m_WindPre[0].use == false)
		{
			m_TenguPre.frame = 0;
			m_TenguPre.stateteng = TENGU_STATE_STAY;
		}

	}
}


void TENGU::DeletePre(void)
{
	//分身を消す前に初期化
	m_TenguPre.stateteng = TENGU_STATE_STAY;
	m_TenguPre.nomalFlag = true;
	m_TenguPre.thunderAtkFrag = false;
	m_TenguPre.fireFlag = false;
	m_TenguPre.windFlag = false;
	m_TenguPre.animeCounter = 0;
	m_TenguPre.animePtn = 0.0f;

	m_TenguPre.pos = D3DXVECTOR2(-100.0f, -100.0f);
	m_CloudPre.use = false;

	m_ThunderPre.use = false;

	for (int i = 0; i < 3; i++)
	{
		m_FirePre[i].speed = 3.0f;
		m_FirePre[i].onGround = false;
		m_FirePre[i].use = false;
	}

	for (int i = 0; i < 2; i++)
	{
		m_WindPre[i].use = false;
		m_WindPre[i].speed.x = frand() * 10.0 - 5.0f;
		m_WindPre[i].speed.y = -1.0f;
	}

	m_TenguPre.use = false;
}

void TENGU::TenguExp(void)
{
	m_Exp.use = true;
	if (m_Exp.anmFrame >= ANIMATION_COUNT)
	{
		m_Exp.anmPtn++;
		m_Exp.anmFrame = 0.0f;
	}
	m_Exp.anmFrame++;

	if (m_Exp.anmPtn >= 6)
	{
		m_Exp.use = false;
	}
}

void TENGU::TextureFlagManager(bool* Tflag)
{
	m_Tengu.nomalFlag = false;
	m_Tengu.thunderAtkFrag = false;
	m_Tengu.thunderHitFlag = false;
	m_Tengu.fallFlag = false;
	m_Tengu.downFlag = false;
	m_Tengu.texHitFlag = false;
	m_Tengu.fireFlag = false;
	m_Tengu.windFlag = false;

	*Tflag = true;
}

void TENGU::TextureFlagManagerPre(bool* Tflag)
{
	m_TenguPre.nomalFlag = false;
	m_TenguPre.thunderAtkFrag = false;
	m_TenguPre.thunderHitFlag = false;
	m_TenguPre.fallFlag = false;
	m_TenguPre.downFlag = false;
	m_TenguPre.texHitFlag = false;
	m_TenguPre.fireFlag = false;
	m_TenguPre.windFlag = false;

	*Tflag = true;
}
//----------------------------------------------------------------------------
