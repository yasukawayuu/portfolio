#pragma once
#include "component.h"

class Object3D : public Component
{
private:
	unsigned int m_DrawIndex{};
public:
	void Init(const char* FileName);
	void Draw();
};