#pragma once

#include "component.h"
#define PARTICLE_NUM (100)

class Particle : public Component
{
private:
	D3DXVECTOR3 m_Position[PARTICLE_NUM]{};
	D3DXVECTOR3 m_Velocity[PARTICLE_NUM]{};
	float		m_StartTime[PARTICLE_NUM]{};
	float		m_OldStartTime[PARTICLE_NUM]{};
	float		m_Vanishing[PARTICLE_NUM]{};
	D3DXVECTOR3	m_EndPositon{};
	D3DXCOLOR m_Color[PARTICLE_NUM]{};
	D3DXCOLOR m_EndColor{};
public:
	void Init() override;
	void Update() override;
	void Draw() override;
};