#pragma once

class Fade;
#include "scene.h"

class Result : public Scene
{
private:
	Fade* m_Fade;
public:
	void Init() override;
	void Update() override;
};