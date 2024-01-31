
#include "main.h"
#include "renderer.h"
#include "particle.h"
#include "textureManager.h"
#include <random>

void Particle::Init()
{
	std::random_device rd; //乱数生成器の作成
	std::mt19937 mt(rd()); //メル11センヌ・ツイスター
	std::uniform_real_distribution<float> random(-0.1f, 0.1f);//小数の乱数
	
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		m_Velocity[i].x = random(mt);
		m_Velocity[i].y = 0.02f;
		m_Velocity[i].z = random(mt);
		m_StartTime[i] = i;
		m_OldStartTime[i] = i;
		m_Vanishing[i] = 7.0f;
		m_Color[i] = D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f);
	}
	m_EndPositon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EndColor = D3DXCOLOR(1.0f, 0.95, 0.0f,0.0f);
}

void Particle::Update()
{
	

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		if (m_StartTime[i] < 0.0f)
		{
			if (m_Color[i].g < m_EndColor.g)
				m_Color[i].g += 0.1f;

			if (m_Color[i].a > m_EndColor.a)
				m_Color[i].a -= 0.005;

			m_Vanishing[i] -= 1.0f;
		}

		if(m_StartTime[i] < 0.0f && m_Vanishing[i] > 6.0f)
			m_Position[i] += m_Velocity[i];

		if (m_Vanishing[i] > 0.0f && m_Vanishing[i] < 6.0f)
		{
			if (m_Position[i].x > 0.0f)
				m_Position[i].x -= 0.1f;

			if (m_Position[i].x < 0.0f)
				m_Position[i].x += 0.1f;

			if (m_Position[i].z > 0.0f)
				m_Position[i].z -= 0.1f;

			if (m_Position[i].z < 0.0f)
				m_Position[i].z += 0.1f;

			m_Position[i].y += m_Velocity[i].y;
		}

		if (m_Vanishing[i] < 0.0f)
		{
			m_StartTime[i] = m_OldStartTime[i];
			m_Vanishing[i] = 8.0f;
			m_Position[i].x = 0.0f;
			m_Position[i].y = 0.0f;
			m_Position[i].z = 0.0f;
			m_Color[i] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}

		


		


		m_StartTime[i] -= 0.2f;
		
	}
}

void Particle::Draw()
{
	for (int i = 0 ;i< PARTICLE_NUM; i++)
	{
		if(m_StartTime[i] <= 0.0f && m_Vanishing[i] >= 0.0f)
		TextureManager::GetInstance()->Draw3D("maru", m_Position[i], 0.03f, 0.03f, 0.0f, 0.0f, 1.0f, 1.0f, m_Color[i]);

	}
}
