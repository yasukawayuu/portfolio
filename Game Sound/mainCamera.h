#pragma once

#include "gameObject.h"

class MainCamera : public GameObject
{
private:

	D3DXVECTOR3	m_Target{};
	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix{};

	float m_ShakeAmplitude{};
	int m_ShakeTime{};
	float m_ShakeOffset{};

public:
	void Init();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix(void) const { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position, float Size);
	void Shake(float Amplitude) { m_ShakeAmplitude = Amplitude; }
};