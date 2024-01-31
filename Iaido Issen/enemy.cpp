#include "enemy.h"

void ENEMY::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/normalenemy.png");
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
	m_speed = 3.0f;
	m_use = false;
	m_LR = 0;
}

void ENEMY::Uninit(void)
{

}

void ENEMY::Update(void)
{
	if (m_use == true)
	{

		if (m_pos.x > m_right)
		{
			m_speed *= -1;
			m_LR += 1;
		}

		if (m_pos.x < m_left)
		{
			m_speed *= -1;
			m_LR -= 1;
		}

		m_pos.x += m_speed;
	}


	if (m_animeCount > 15)
	{
		m_animePtn++;

		if (m_animePtn > 3)
			m_animePtn = 0;

		m_animeCount = 0;
	}

	m_animeCount++;
}

void ENEMY::Draw(void)
{
	if (m_use == true)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos.x,
			m_base->y + m_pos.y,
			192.0f, 256.0f,
			m_u[m_animePtn], m_v[m_LR], 0.3333f, 0.5f);
	}
}

void ENEMY::SetEnemy(D3DXVECTOR2 pos,bool use,float range,float left,float right)
{
	m_pos = pos;
	m_use = use;
	m_left = left + range / 2;
	m_right = right - range /2;
}

