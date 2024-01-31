
#include "obstacle.h"


void OBSTACLE::Init(void)
{
	m_texture = LoadTexture((char*)"data/TEXTURE/“I.png");
	m_pos = D3DXVECTOR2(1400.0f, 730.0f);
	m_size = 384.0f;
	m_collisionuse = false;

	m_animePtn = 0;
	m_animeCounter = 0;

}

void OBSTACLE::Uninit(void)
{
}

void OBSTACLE::Update(void)
{
	if (m_collisionuse == false)
	{
		if (m_animePtn < 2)
		{
			if (m_animeCounter > 30)
			{
				m_animePtn += 1;
				m_animeCounter = 0;
			}

			m_animeCounter++;
		}

	}
}

void OBSTACLE::Draw(void)
{

	DrawSpriteColor(m_texture,
		m_base->x + m_pos.x,
		m_base->y + m_pos.y,
		m_size, m_size,
		m_animeTable[m_animePtn],
		0.0f,
		0.333f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

D3DXVECTOR2 * OBSTACLE::GetObstaclePos(void)
{
	return &m_pos;
}

bool * OBSTACLE::GetCollisionPos(void)
{
	return &m_collisionuse;
}

float * OBSTACLE::GetObstacleSize(void)
{
	return &m_size;
}


