#pragma once
#include "scene.h"

class Loading : public Scene
{
private:
	GameObject* m_Loading{};
public:
	void Init() override;
	void Update() override;
};