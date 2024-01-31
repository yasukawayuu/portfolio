#pragma once
class Audio;

#include "gameObject.h"

class Box : public GameObject
{
private:
	Audio* m_WaterDrop;
	std::vector<int> m_Probability = { 95,1,1,1,1,1 };
public:

	void Init();
	void Update();
	void Draw();
};