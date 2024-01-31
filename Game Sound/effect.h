#pragma once

#include "gameObject.h"

class Effect : public GameObject
{
private:
	int m_Count = 0;
	int m_EffectNo = 0;
	int m_U = 0, m_V = 0;
	bool m_DoTracking = false;
	D3DXVECTOR3* m_Target{};
	float m_Correction = 0.0f;
public:

	void Init();
	void Update();
	void Draw();

	void SetEffectNo(int no) { m_EffectNo = no; }
	void SetUV(int u, int v) { m_U = u; m_V = v; }
	void SetTracking(bool tracking, D3DXVECTOR3* target, float m_correction) { m_DoTracking = tracking; m_Target = target; m_Correction = m_correction; }
};