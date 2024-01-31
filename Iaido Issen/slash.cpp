#include "slash.h"

void SLASH::Init(void)
{
	m_TextureSHLeft = LoadTexture((char*)"data/TEXTURE/LeftSlash.png");
	m_TextureSHRight = LoadTexture((char*)"data/TEXTURE/RightSlash.png");


}

void SLASH::Uninit(void)
{
	
}

void SLASH::Update(void)
{
	if (m_time == 0)
	{
		m_use = false;
		m_Effect->ResetSlash();
	}
	else
	{
		m_time -= 10.0f;
	}
}

void SLASH::Draw(void)
{

	if (m_use == true)
	{
		switch (m_muki)
		{
		case 0:
			DrawSpriteColorRotate(m_TextureSHLeft, m_base->x + m_pos.x + m_mukiTalbel[m_muki], m_base->y + m_pos.y + 5, 256.0f, 256.0f,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			break;
		case 1:
			DrawSpriteColorRotate(m_TextureSHRight, m_base->x + m_pos.x + m_mukiTalbel[m_muki], m_base->y + m_pos.y, 256.0f, 256.0f,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			break;
		case 2:
			DrawSpriteColorRotate(m_TextureSHLeft, m_base->x + m_pos.x + m_mukiTalbel[m_muki], m_base->y + m_pos.y + 5, 256.0f, 256.0f,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			break;
		case 3:
			DrawSpriteColorRotate(m_TextureSHRight, m_base->x + m_pos.x + m_mukiTalbel[m_muki], m_base->y + m_pos.y, 256.0f, 256.0f,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			break;
		}

	}
}

void SLASH::SetSlash(D3DXVECTOR2 pos, int muki)
{
	m_pos = pos;

	m_use = true;

	m_time = 180.0f;

	m_muki = muki;

	
	m_Effect->SetSlashEffect(D3DXVECTOR2(m_pos.x + m_mukiTalbel[m_muki], m_pos.y), m_muki);
	
}

D3DXVECTOR2 * SLASH::GetSlashPos(void)
{
	return &m_pos;
}

bool * SLASH::GetSlashUse(void)
{
	return &m_use;
}
