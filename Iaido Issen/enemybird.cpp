#include "enemybird.h"

void ENEMYBIRD::Init(void)
{
	m_Texturered = LoadTexture((char*)"data/TEXTURE/enemybird/enembirdred.png");
	m_Texturepurple = LoadTexture((char*)"data/TEXTURE/enemybird/enembirdpurple.png");
	m_Textureyellow = LoadTexture((char*)"data/TEXTURE/enemybird/enembirdyellow.png");

	m_fire.m_Texture = LoadTexture((char*)"data/TEXTURE/tengu/fire1.png");
	m_wind.m_Texture = LoadTexture((char*)"data/TEXTURE/tengu/strom1.png");
	m_thundercould.m_Texture = LoadTexture((char*)"data/TEXTURE/tengu/cloud1.png");
	m_thunder.m_Texture = LoadTexture((char*)"data/TEXTURE/tengu/kaminari1.png");
	m_fire.use = false;
	m_wind.use = false;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
	m_use = false;
	m_upflag = false;
	m_frame = 0.0f;
	m_speed = 5.0f;
	
}

void ENEMYBIRD::Uninit(void)
{

}

void ENEMYBIRD::Update(void)
{
	if (m_use == true)
	{
		if (m_pos.x > m_playerpos->x)
		{
			m_LR = 0;
		}
		else
		{
			m_LR = 1;
		}

		if (m_animeCount > 10)
		{
			m_animePtn++;

			if (m_animePtn > 1)
				m_animePtn = 0;

			m_animeCount = 0;
		}

		m_animeCount++;

		if (m_elementanimeCount > 7)
		{
			m_elementanimePtn++;
			if (m_elementanimePtn > 25)
				m_elementanimePtn = 0;

			m_elementanimeCount = 0;
		}

		m_elementanimeCount++;

	



		switch (m_pattern)
		{
		case ENEMYBIRD_UP:
			BirdUp();
			break;
		case ENEMYBIRD_THUNDERATTACK:
			BirdThunderAttack();
			break;
		case EMEMYBIRD_TURNING:
			BirdTurning();
			break;
		case ENEMYBIRD_FIREATTACK:
			BirdFireAttack();
			break;
		case ENEMYBIRD_WINDATTACK:
			BirdWindAttack();
			break;
		}
	}
}

void ENEMYBIRD::Draw(void)
{


	if (m_use == true)
	{
		if (m_pattern == ENEMYBIRD_THUNDERATTACK || m_pattern == ENEMYBIRD_UP || m_pattern == EMEMYBIRD_TURNING)
		{
		  DrawSprite(m_Textureyellow,
			m_base->x + m_pos.x,
			m_base->y + m_pos.y,
			256.0f, 256.0f,
			m_u[m_animePtn], m_v[m_LR], 0.3333f, 0.5f);
		}

		if (m_pattern == ENEMYBIRD_FIREATTACK)
		{
			DrawSprite(m_Texturered,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y,
				256.0f, 256.0f,
				m_u[m_animePtn], m_v[m_LR], 0.3333f, 0.5f);
		}


		if (m_pattern == ENEMYBIRD_WINDATTACK)
		{
			DrawSprite(m_Texturepurple,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y,
				256.0f, 256.0f,
				m_u[m_animePtn], m_v[m_LR], 0.3333f, 0.5f);
		}

		if (m_fire.use == true)
		{
			DrawSprite(m_fire.m_Texture,
				m_base->x + m_fire.m_pos.x,
				m_base->y + m_fire.m_pos.y,
				256.0f, 256.0f,
				m_elementanimePtn / 5, ((int)m_elementanimePtn) % 5 / 5.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f);
		}

		if (m_wind.use == true)
		{
			DrawSprite(m_wind.m_Texture,
				m_base->x + m_wind.m_pos.x,
				m_base->y + m_wind.m_pos.y,
				256.0f, 256.0f,
				m_elementanimePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f);
		}
	}

	if (m_thundercould.use == true && m_use == true)
	{
		
		DrawSprite(m_thunder.m_Texture,
			m_base->x + m_thunder.m_pos.x,
			m_base->y + m_thunder.m_pos.y,
			256.0f, 256.0f,
			m_elementanimePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);

		DrawSprite(m_thundercould.m_Texture,
			m_base->x + m_thundercould.m_pos.x,
			m_base->y + m_thundercould.m_pos.y,
			256.0f, 256.0f,
			m_animePtn / 2.0f, 0.0f, 1.0f / 2.0f, 1.0f);
	}
	
}


void ENEMYBIRD::BirdWait(void)
{

}

void ENEMYBIRD::BirdUp(void)
{
	D3DXVECTOR2 dist = *m_playerpos - m_pos;
	float len = D3DXVec2Length(&dist);

	if (len < SCREEN_WIDTH / 2)
	{
		m_upflag = true;
	}

	if (m_upflag == true)
	{
		m_pos.y -= 5.0f;
		if (m_pos.y < 500.0f)
		{
			m_pattern = ENEMYBIRD_THUNDERATTACK;
		}
	}
}

void ENEMYBIRD::BirdThunderAttack(void)
{
	

	D3DXVECTOR2 dist = *m_playerpos - m_thundercould.m_pos;
	float len = D3DXVec2Length(&dist);


	if (len < SCREEN_WIDTH / 2)
	{
		m_frame++;

		D3DXVECTOR2 dsit = *m_playerpos - m_thundercould.m_pos;
		D3DXVec2Normalize(&dsit, &dsit);
		m_thundercould.m_pos.x += (dsit.x * 10.0f);

		
	}

	if (m_frame > 60.0f)
	{
		m_animePtn = 2;
		m_thunder.m_pos.y += 10.0f;
	}
	else
	{
		m_thunder.m_pos.x = m_thundercould.m_pos.x;
	}
	

	if (m_thunder.m_pos.y > SCREEN_HEIGHT)
	{
		m_frame = 0.0f;
		m_thunder.m_pos = m_thundercould.m_pos;
	}
	


}


void ENEMYBIRD::BirdTurning(void)
{
	m_frame++;
	D3DXVECTOR2 dist = *m_playerpos - m_pos;
	float len = D3DXVec2Length(&dist);
	m_pos = m_enoriginpos;
	m_pos.x += cosf(2 * D3DX_PI / 2 + m_rotate) * 500.0f;
	m_pos.y += sinf(2 * D3DX_PI / 2 + m_rotate) * 100.0f;
	m_rotate += 0.01f;

	if (len < SCREEN_WIDTH / 2 && m_frame > 240.0f)
	{
		m_originpos = m_pos;
		m_frame = 0.0f;
		m_pattern = ENEMYBIRD_THUNDERATTACK;
	}
}


void ENEMYBIRD::BirdFireAttack(void)
{
	D3DXVECTOR2 dist = *m_playerpos - m_pos;
	float len = D3DXVec2Length(&dist);

	if (len < SCREEN_WIDTH / 2)
	{
		m_fire.use = true;
	}

	if (m_fire.use == true)
	{
		if (m_fire.m_oldplayerpos == D3DXVECTOR2(0.0f, 0.0f))
		{
			m_fire.m_oldplayerpos = *m_playerpos;
		}

		D3DXVECTOR2 dist = m_fire.m_oldplayerpos - m_fire.m_pos;
		float len = D3DXVec2Length(&dist);

		if (len > 5)
		{
			D3DXVECTOR2 dsit = m_fire.m_oldplayerpos - m_fire.m_pos;
			D3DXVec2Normalize(&dsit, &dsit);
			m_fire.m_pos += (dsit * 4.0f);
			m_animePtn = 2;
		}

		if (len < 5)
		{
			m_fire.m_oldplayerpos = D3DXVECTOR2(0.0f, 0.0f);
			m_fire.m_pos = m_pos;
			m_fire.use = false;
		}
	}
}

void ENEMYBIRD::BirdWindAttack(void)
{
	D3DXVECTOR2 dist = *m_playerpos - m_pos;
	float len = D3DXVec2Length(&dist);

	if (len < SCREEN_WIDTH / 2)
	{
		m_wind.use = true;
	}

	if (m_wind.use == true)
	{
		if (m_wind.m_oldplayerpos == D3DXVECTOR2(0.0f, 0.0f))
		{
			m_wind.m_oldplayerpos = *m_playerpos;
		}

		D3DXVECTOR2 dist = m_wind.m_oldplayerpos - m_wind.m_pos;
		float len = D3DXVec2Length(&dist);

		if (len > 5)
		{
			D3DXVECTOR2 dsit = m_wind.m_oldplayerpos - m_wind.m_pos;
			D3DXVec2Normalize(&dsit, &dsit);
			m_wind.m_pos += (dsit * 4.0f);
			m_animePtn = 2;
		}

		if (len < 5)
		{
			m_wind.m_oldplayerpos = D3DXVECTOR2(0.0f, 0.0f);
			m_wind.m_pos = m_pos;
			m_wind.use = false;
		}
	}	
}

void ENEMYBIRD::BirdMove(void)
{

}


void ENEMYBIRD::SetEnemy(D3DXVECTOR2 pos, bool use,ENEMYBIRD_PATTERN pattern)
{
	m_pos = pos;
	m_originpos = pos;
	m_enoriginpos = pos;
	m_use = use;
	m_pattern = pattern;
	m_fire.m_pos = pos;
	m_wind.m_pos = pos;
	m_thunder.m_pos = D3DXVECTOR2(m_pos.x, 64.0f);
	m_thundercould.m_pos = D3DXVECTOR2(m_pos.x, 64.0f);

	if (m_pattern == ENEMYBIRD_THUNDERATTACK || m_pattern == ENEMYBIRD_UP || m_pattern == EMEMYBIRD_TURNING)
	{
		m_thundercould.use = true;
		m_thunder.use = true;
	}
}

