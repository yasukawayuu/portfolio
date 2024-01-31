#include "effect.h"
#include "input.h"

void EFFECT::Init(void)
{
	m_TextureKyuubiSand = LoadTexture((char*)"data/TEXTURE/effect/KyuubiSand.png");
	m_TextureSlash = LoadTexture((char*)"data/TEXTURE/effect/slash.png");
	m_TextureBlood = LoadTexture((char*)"data/TEXTURE/effect/blood.png");
	m_TextureCharge = LoadTexture((char*)"data/TEXTURE/effect/charge1.png");
	m_TextureDeath = LoadTexture((char*)"data/TEXTURE/effect/death.png");
	m_TextureHit = LoadTexture((char*)"data/TEXTURE/effect/hit.png");
	m_TextureOverheat = LoadTexture((char*)"data/TEXTURE/effect/overheat.png");
	m_TextureRun = LoadTexture((char*)"data/TEXTURE/effect/run_effect.png");
	m_TextureTeleportation = LoadTexture((char*)"data/TEXTURE/effect/shunkanidou_shougeki.png");
	m_TextureKyuubiTele = LoadTexture((char*)"data/TEXTURE/effect/shunkanidou.png");
	m_TextureKyuubiCharge = LoadTexture((char*)"data/TEXTURE/effect/KyuubiCharge.png");


	m_Flag = 0;

	//九尾攻撃時の砂埃の初期化
	ResetKyuubiSand();
	//斬撃の初期化
	ResetSlash();
	//血液の初期化
	ResetBlood();
	//チャージの初期化
	ResetCharge();
	//死亡時演出の初期化
	ResetDeath();
	//ヒットの初期化
	ResetHit();
	//オーバーヒートの初期化
	ResetOverheat();
	//通常移動の初期化
	ResetRun();
	//瞬間移動の初期化
	ResetTeleportation();
	//九尾の瞬間移動の初期化
	ResetKyuubiTele();
	//九尾の魔力溜めの初期化
	ResetKyuubiCharge();
	
}

void EFFECT::Uninit(void)
{
}

void EFFECT::Update(void)
{
	if (m_KyuubiSand.use == true)
	{
		//九尾攻撃時アニメーション
		if (m_KyuubiSand.animeCounter > m_KyuubiSand.patternWait)
		{
			m_KyuubiSand.animePtn++;

			if (m_KyuubiSand.animePtn >= m_KyuubiSand.patternMax)
				m_KyuubiSand.animePtn = 0;

			m_KyuubiSand.animeCounter = 0;
		}
		m_KyuubiSand.animeCounter++;
	}

	if (m_Slash.use == true)
	{
		//斬撃アニメーション
		if (m_Slash.animeCounter > m_Slash.patternWait)
		{
			m_Slash.animePtn++;

			if (m_Slash.animePtn >= m_Slash.patternMax)
				m_Slash.animePtn = 0;

			m_Slash.animeCounter = 0;
		}
		m_Slash.animeCounter++;
	}

	if (m_Blood.use == true)
	{
		//血液アニメーション
		if (m_Blood.animeCounter > m_Blood.patternWait)
		{
			m_Blood.animePtn++;

			if (m_Blood.animePtn >= m_Blood.patternMax)
				m_Blood.animePtn = 0;

			m_Blood.animeCounter = 0;
		}
		m_Blood.animeCounter++;
	}

	if (m_Charge.use == true)
	{
		//チャージアニメーション
		if (m_Charge.animeCounter > m_Charge.patternWait)
		{
			m_Charge.animePtn++;

			if (m_Flag == 0)
			{
				if (m_Charge.animePtn >= 20)
					m_Charge.animePtn = 20;
			}
			if (m_Flag == 2)
			{
				if (m_Charge.animePtn >= m_Charge.patternMax)
					m_Charge.use = false;
			}

			m_Charge.animeCounter = 0;
		}
		m_Charge.animeCounter++;
	}

	if (m_Death.use == true)
	{
		//死亡時演出アニメーション
		if (m_Death.animeCounter > m_Death.patternWait)
		{
			m_Death.animePtn++;

			if (m_Death.animePtn >= m_Death.patternMax)
				m_Death.animePtn = 0;

			m_Death.animeCounter = 0;
		}
		m_Death.animeCounter++;
	}

	if (m_Hit.use == true)
	{
		//ヒットアニメーション
		if (m_Hit.animeCounter > m_Hit.patternWait)
		{
			m_Hit.animePtn++;

			if (m_Hit.animePtn >= m_Hit.patternMax)
				m_Hit.animePtn = 0;

			m_Hit.animeCounter = 0;
		}
		m_Hit.animeCounter++;
	}

	if (m_Overheat.use == true)
	{
		//オーバーヒートアニメーション
		if (m_Overheat.animeCounter > m_Overheat.patternWait)
		{
			m_Overheat.animePtn++;

			if (m_Overheat.animePtn >= m_Overheat.patternMax)
				m_Overheat.animePtn = 0;

			m_Overheat.animeCounter = 0;
		}
		m_Overheat.animeCounter++;
	}

	if (m_Run.use == true)
	{
		//通常移動アニメーション
		if (m_Run.animeCounter > m_Run.patternWait)
		{
			m_Run.animePtn++;

			if (m_Run.animePtn >= m_Run.patternMax)
				m_Run.animePtn = 0;

			m_Run.animeCounter = 0;
		}
		m_Run.animeCounter++;
	}

	if (m_Teleportation.use == true)
	{
		//瞬間移動アニメーション
		if (m_Teleportation.animeCounter > m_Teleportation.patternWait)
		{
			m_Teleportation.animePtn++;

			if (m_Teleportation.animePtn >= m_Teleportation.patternMax)
				ResetTeleportation();
			
			m_Teleportation.animeCounter = 0;
		}
		m_Teleportation.animeCounter++;
	}

	if (m_KyuubiTele.use == true)
	{
		//九尾瞬間移動時アニメーション
		if (m_KyuubiTele.animeCounter > m_KyuubiTele.patternWait)
		{
			m_KyuubiTele.animePtn++;

			if (m_KyuubiTele.animePtn >= m_KyuubiTele.patternMax)
				ResetKyuubiTele();

			m_KyuubiTele.animeCounter = 0;
		}
		m_KyuubiTele.animeCounter++;
	}

	if (m_KyuubiCharge.use == true)
	{
		//九尾の魔力溜めアニメーション
		if (m_KyuubiCharge.animeCounter > m_KyuubiCharge.patternWait)
		{
			m_KyuubiCharge.animePtn++;

			if (m_KyuubiCharge.animePtn >= m_KyuubiCharge.patternMax)
				ResetKyuubiCharge();

			m_KyuubiCharge.animeCounter = 0;
		}
		m_KyuubiCharge.animeCounter++;
	}

	if (m_Flag == 1)
	{
		m_Charge.use = false;
		ResetCharge();
	}

	//デバック用
	/*if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetKyuubiTele(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	}*/
}

void EFFECT::Draw(void)
{
	//九尾攻撃時描画
	if (m_KyuubiSand.use == true)
	{
		DrawSprite(m_TextureKyuubiSand, m_base->x + m_KyuubiSand.pos.x, m_base->y + m_KyuubiSand.pos.y, m_KyuubiSand.wh.x, m_KyuubiSand.wh.y,
			m_KyuubiSand.patternWH.x * (m_KyuubiSand.animePtn % (int)m_KyuubiSand.divide.x),
			m_KyuubiSand.patternWH.y * (m_KyuubiSand.animePtn / (int)m_KyuubiSand.divide.x),
			m_KyuubiSand.patternWH.x, m_KyuubiSand.patternWH.y);
	}

	//斬撃描画
	if (m_Slash.use == true)
	{
		DrawSpriteColorRotate(m_TextureSlash, m_base->x + m_Slash.pos.x, m_base->y + m_Slash.pos.y, m_Slash.wh.x, m_Slash.wh.y,
			m_Slash.patternWH.x * (m_Slash.animePtn % (int)m_Slash.divide.x),
			m_Slash.patternWH.y * (m_Slash.animePtn / (int)m_Slash.divide.x),
			m_Slash.patternWH.x, m_Slash.patternWH.y,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), m_mukiTalbelSlash[m_Slash.muki]);
	}

	//血液描画
	if (m_Blood.use == true)
	{
		DrawSprite(m_TextureBlood, m_base->x + m_Blood.pos.x, m_base->y + m_Blood.pos.y, m_Blood.wh.x, m_Blood.wh.y,
			m_Blood.patternWH.x * (m_Blood.animePtn % (int)m_Blood.divide.x),
			m_Blood.patternWH.y * (m_Blood.animePtn / (int)m_Blood.divide.x),
			m_Blood.patternWH.x, m_Blood.patternWH.y);
	}

	//チャージ描画
	if (m_Charge.use == true)
	{
		DrawSpriteColor(m_TextureCharge, m_base->x + m_Charge.pos.x, m_base->y + m_Charge.pos.y, m_Charge.wh.x, m_Charge.wh.y,
			m_Charge.patternWH.x * (m_Charge.animePtn % (int)m_Charge.divide.x),
			m_Charge.patternWH.y * (m_Charge.animePtn / (int)m_Charge.divide.x),
			m_Charge.patternWH.x, m_Charge.patternWH.y,D3DXCOLOR(1.0f,1.0f,1.0f,0.5f));
	}

	//死亡時演出描画
	if (m_Death.use == true)
	{
		DrawSprite(m_TextureDeath, m_base->x + m_Death.pos.x, m_base->y + m_Death.pos.y, m_Death.wh.x, m_Death.wh.y,
			m_Death.patternWH.x * (m_Death.animePtn % (int)m_Death.divide.x),
			m_Death.patternWH.y * (m_Death.animePtn / (int)m_Death.divide.x),
			m_Death.patternWH.x, m_Death.patternWH.y);
	}

	//ヒット描画
	if (m_Hit.use == true)
	{
		DrawSprite(m_TextureHit, m_base->x + m_Hit.pos.x, m_base->y + m_Hit.pos.y, m_Hit.wh.x, m_Hit.wh.y,
			m_Hit.patternWH.x * (m_Hit.animePtn % (int)m_Hit.divide.x),
			m_Hit.patternWH.y * (m_Hit.animePtn / (int)m_Hit.divide.x),
			m_Hit.patternWH.x, m_Hit.patternWH.y);
	}

	//オーバーヒート描画
	if (m_Overheat.use == true)
	{
		DrawSprite(m_TextureOverheat, m_base->x + m_Overheat.pos.x, m_base->y + m_Overheat.pos.y, m_Overheat.wh.x, m_Overheat.wh.y,
			m_Overheat.patternWH.x * (m_Overheat.animePtn % (int)m_Overheat.divide.x),
			m_Overheat.patternWH.y * (m_Overheat.animePtn / (int)m_Overheat.divide.x),
			m_Overheat.patternWH.x, m_Overheat.patternWH.y);
	}

	//通常移動描画
	if (m_Run.use == true)
	{
		DrawSprite(m_TextureRun, m_base->x + m_Run.pos.x, m_base->y + m_Run.pos.y, m_Run.wh.x, m_Run.wh.y,
			m_Run.patternWH.x * (m_Run.animePtn % (int)m_Run.divide.x),
			m_Run.patternWH.y * (m_Run.animePtn / (int)m_Run.divide.x),
			m_Run.patternWH.x, m_Run.patternWH.y);
	}

	//瞬間移動描画
	if (m_Teleportation.use == true)
	{
		DrawSpriteColorRotate(m_TextureTeleportation,m_base->x + m_Teleportation.pos.x, m_base->y + m_Teleportation.pos.y, m_Teleportation.wh.x, m_Teleportation.wh.y,
			m_Teleportation.patternWH.x * (m_Teleportation.animePtn % (int)m_Teleportation.divide.x),
			m_Teleportation.patternWH.y * (m_Teleportation.animePtn / (int)m_Teleportation.divide.x),
			m_Teleportation.patternWH.x, m_Teleportation.patternWH.y,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), m_mukiTalbelTeleportation[m_Slash.muki]);
	}

	//九尾瞬間移動時描画
	if (m_KyuubiTele.use == true)
	{
		DrawSprite(m_TextureKyuubiTele, m_base->x + m_KyuubiTele.pos.x, m_base->y + m_KyuubiTele.pos.y, m_KyuubiTele.wh.x, m_KyuubiTele.wh.y,
			m_KyuubiTele.patternWH.x * (m_KyuubiTele.animePtn % (int)m_KyuubiTele.divide.x),
			m_KyuubiTele.patternWH.y * (m_KyuubiTele.animePtn / (int)m_KyuubiTele.divide.x),
			m_KyuubiTele.patternWH.x, m_KyuubiTele.patternWH.y);
	}

	//九尾の魔力溜め描画
	if (m_KyuubiCharge.use == true)
	{
		DrawSprite(m_TextureKyuubiCharge, m_base->x + m_KyuubiCharge.pos.x, m_base->y + m_KyuubiCharge.pos.y, m_KyuubiCharge.wh.x, m_KyuubiCharge.wh.y,
			m_KyuubiCharge.patternWH.x * (m_KyuubiCharge.animePtn % (int)m_KyuubiCharge.divide.x),
			m_KyuubiCharge.patternWH.y * (m_KyuubiCharge.animePtn / (int)m_KyuubiCharge.divide.x),
			m_KyuubiCharge.patternWH.x, m_KyuubiCharge.patternWH.y);
	}
}

//九尾攻撃時設定
void EFFECT::SetKyuubiSand(D3DXVECTOR2 pos)
{
	m_KyuubiSand.pos = pos;

	m_KyuubiSand.use = true;

}
//斬撃設定
void EFFECT::SetSlashEffect(D3DXVECTOR2 pos,int muki)
{
	m_Slash.pos = pos;

	m_Slash.muki = muki;

	m_Slash.use = true;

}
//血液設定
void EFFECT::SetBlood(D3DXVECTOR2 pos)
{
	m_Blood.pos = pos;

	m_Blood.use = true;

}
//チャージ設定
void EFFECT::SetCharge(D3DXVECTOR2 pos)
{
	m_Charge.pos = pos;

	m_Charge.use = true;

}
//死亡時演出設定
void EFFECT::SetDeath(D3DXVECTOR2 pos)
{
	m_Death.pos = pos;

	m_Death.use = true;

}
//ヒット設定
void EFFECT::SetHit(D3DXVECTOR2 pos)
{
	m_Hit.pos = pos;

	m_Hit.use = true;

}
//オーバーヒート設定
void EFFECT::SetOverheat(D3DXVECTOR2 pos)
{
	m_Overheat.pos = pos;

	m_Overheat.use = true;

}
//通常移動設定
void EFFECT::SetRun(D3DXVECTOR2 pos)
{
	m_Run.pos = pos;

	m_Run.use = true;

}
//瞬間移動設定
void EFFECT::SetTeleportation(D3DXVECTOR2 pos)
{
	m_Teleportation.pos = pos;

	m_Teleportation.use = true;

}
//九尾の瞬間移動
void EFFECT::SetKyuubiTele(D3DXVECTOR2 pos)
{
	m_KyuubiTele.pos = pos;

	m_KyuubiTele.use = true;
}
//九尾の魔力溜め
void EFFECT::SetKyuubiCharge(D3DXVECTOR2 pos)
{
	m_KyuubiCharge.pos = pos;

	m_KyuubiCharge.use = true;
}
//九尾攻撃時初期値設定
void EFFECT::ResetKyuubiSand(void)
{
	m_KyuubiSand.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_KyuubiSand.wh = D3DXVECTOR2(64.0f, 64.0f);
	m_KyuubiSand.use = false;
	m_KyuubiSand.animeCounter = 0;
	m_KyuubiSand.animePtn = 0;
	m_KyuubiSand.divide = D3DXVECTOR2(4, 3);
	m_KyuubiSand.patternWH = D3DXVECTOR2((1.0 / m_KyuubiSand.divide.x), (1.0 / m_KyuubiSand.divide.y));
	m_KyuubiSand.patternMax = m_KyuubiSand.divide.x * m_KyuubiSand.divide.y;
	m_KyuubiSand.patternWait = 3;
}
//斬撃初期値設定
void EFFECT::ResetSlash(void)
{
	m_Slash.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Slash.wh = D3DXVECTOR2(256.0f, 256.0f);
	m_Slash.use = false;
	m_Slash.animeCounter = 0;
	m_Slash.animePtn = 0;
	m_Slash.divide = D3DXVECTOR2(3,2);
	m_Slash.patternWH = D3DXVECTOR2((1.0 / m_Slash.divide.x), (1.0 / m_Slash.divide.y));
	m_Slash.patternMax = m_Slash.divide.x * m_Slash.divide.y;
	m_Slash.patternWait = 3;
}
//血液設定
void EFFECT::ResetBlood(void)
{
	m_Blood.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Blood.wh = D3DXVECTOR2(128.0f, 128.0f);
	m_Blood.use = false;
	m_Blood.animeCounter = 0;
	m_Blood.animePtn = 0;
	m_Blood.divide = D3DXVECTOR2(4, 3);
	m_Blood.patternWH = D3DXVECTOR2((1.0 / m_Blood.divide.x), (1.0 / m_Blood.divide.y));
	m_Blood.patternMax = m_Blood.divide.x * m_Blood.divide.y;
	m_Blood.patternWait = 3;
}
//チャージ初期値設定
void EFFECT::ResetCharge(void)
{
	m_Charge.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Charge.wh = D3DXVECTOR2(600.0f, 600.0f);
	m_Charge.use = false;
	m_Charge.animeCounter = 0;
	m_Charge.animePtn = 0;
	m_Charge.divide = D3DXVECTOR2(4, 7);
	m_Charge.patternWH = D3DXVECTOR2((1.0 / m_Charge.divide.x), (1.0 / m_Charge.divide.y));
	m_Charge.patternMax = m_Charge.divide.x * m_Charge.divide.y;
	m_Charge.patternWait = 3;
	m_Flag = 0;
}
//死亡時演出初期値設定
void EFFECT::ResetDeath(void)
{
	m_Death.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Death.wh = D3DXVECTOR2(64.0f, 64.0f);
	m_Death.use = false;
	m_Death.animeCounter = 0;
	m_Death.animePtn = 0;
	m_Death.divide = D3DXVECTOR2(4, 3);
	m_Death.patternWH = D3DXVECTOR2((1.0 / m_Death.divide.x), (1.0 / m_Death.divide.y));
	m_Death.patternMax = m_Death.divide.x * m_Death.divide.y;
	m_Death.patternWait = 3;
}
//ヒット初期値設定
void EFFECT::ResetHit(void)
{
	m_Hit.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Hit.wh = D3DXVECTOR2(256.0f, 256.0f);
	m_Hit.use = false;
	m_Hit.animeCounter = 0;
	m_Hit.animePtn = 0;
	m_Hit.divide = D3DXVECTOR2(4, 2);
	m_Hit.patternWH = D3DXVECTOR2((1.0 / m_Hit.divide.x), (1.0 / m_Hit.divide.y));
	m_Hit.patternMax = m_Hit.divide.x * m_Hit.divide.y;
	m_Hit.patternWait = 3;
}
//オーバーヒート初期値設定
void EFFECT::ResetOverheat(void)
{
	m_Overheat.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Overheat.wh = D3DXVECTOR2(64.0f, 64.0f);
	m_Overheat.use = false;
	m_Overheat.animeCounter = 0;
	m_Overheat.animePtn = 0;
	m_Overheat.divide = D3DXVECTOR2(4, 2);
	m_Overheat.patternWH = D3DXVECTOR2((1.0 / m_Overheat.divide.x), (1.0 / m_Overheat.divide.y));
	m_Overheat.patternMax = m_Overheat.divide.x * m_Overheat.divide.y;
	m_Overheat.patternWait = 3;
}
//通常移動初期値設定
void EFFECT::ResetRun(void)
{
	m_Run.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Run.wh = D3DXVECTOR2(256.0f, 256.0f);
	m_Run.use = false;
	m_Run.animeCounter = 0;
	m_Run.animePtn = 0;
	m_Run.divide = D3DXVECTOR2(4, 3);
	m_Run.patternWH = D3DXVECTOR2((1.0 / m_Run.divide.x), (1.0 / m_Run.divide.y));
	m_Run.patternMax = m_Run.divide.x * m_Run.divide.y;
	m_Run.patternWait = 3;
}
//瞬間移動初期値設定
void EFFECT::ResetTeleportation(void)
{
	m_Teleportation.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Teleportation.wh = D3DXVECTOR2(256.0f,256.0f);
	m_Teleportation.use = false;
	m_Teleportation.animeCounter = 0;
	m_Teleportation.animePtn = 0;
	m_Teleportation.divide = D3DXVECTOR2(5, 6);
	m_Teleportation.patternWH = D3DXVECTOR2((1.0 / m_Teleportation.divide.x), (1.0 / m_Teleportation.divide.y));
	m_Teleportation.patternMax = m_Teleportation.divide.x * m_Teleportation.divide.y;
	m_Teleportation.patternWait = 1;
}
//九尾の瞬間移動初期値設定
void EFFECT::ResetKyuubiTele(void)
{
	m_KyuubiTele.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_KyuubiTele.wh = D3DXVECTOR2(256.0f, 256.0f);
	m_KyuubiTele.use = false;
	m_KyuubiTele.animeCounter = 0;
	m_KyuubiTele.animePtn = 0;
	m_KyuubiTele.divide = D3DXVECTOR2(4, 8);
	m_KyuubiTele.patternWH = D3DXVECTOR2((1.0 / m_KyuubiTele.divide.x), (1.0 / m_KyuubiTele.divide.y));
	m_KyuubiTele.patternMax = m_KyuubiTele.divide.x * m_KyuubiTele.divide.y;
	m_KyuubiTele.patternWait = 1;
}
//九尾の魔力溜め初期値設定
void EFFECT::ResetKyuubiCharge(void)
{
	m_KyuubiCharge.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_KyuubiCharge.wh = D3DXVECTOR2(256.0f, 256.0f);
	m_KyuubiCharge.use = false;
	m_KyuubiCharge.animeCounter = 0;
	m_KyuubiCharge.animePtn = 0;
	m_KyuubiCharge.divide = D3DXVECTOR2(5, 6);
	m_KyuubiCharge.patternWH = D3DXVECTOR2((1.0 / m_KyuubiCharge.divide.x), (1.0 / m_KyuubiCharge.divide.y));
	m_KyuubiCharge.patternMax = m_KyuubiCharge.divide.x * m_KyuubiCharge.divide.y;
	m_KyuubiCharge.patternWait = 3;
}

void EFFECT::SetFlag(int flag)
{
	m_Flag = flag;
}

