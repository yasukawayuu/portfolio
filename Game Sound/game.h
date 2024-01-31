#pragma once

class Audio;
class Fade;
class Enemy;
#include "scene.h"

class Game : public Scene
{
private:
	Audio* m_BGM{};
	Audio* m_BGM1{};
	Audio* m_BGM2{};
	Enemy* m_Enemy{};
	Fade* m_Fade{};
public:


	void Init() override;
	void Update() override;
};