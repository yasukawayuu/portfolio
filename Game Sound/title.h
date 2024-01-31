#pragma once

class Fade; 
class Audio;
#include "scene.h"

class Title : public Scene
{
private:
	Fade* m_Fade;
	Audio* m_BGM;
public:
	void Init() override;
	void Update() override;
};