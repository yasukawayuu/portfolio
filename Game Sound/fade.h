#pragma once

class Sprite;
#include "gameObject.h"

class Fade: public GameObject
{
private:
	Sprite* m_Sprite;
	float m_a = 1.0f;
	bool m_FadeOut = false;
	bool m_FadeFinish = false;
public:
	void Init();
	void Update();
	void FadeOut() { m_FadeOut = true; }
	bool GetFadeOut() { return m_FadeOut; }
	bool GetFadeFinish() { return m_FadeFinish; }
	float GetA() { return m_a; }
};