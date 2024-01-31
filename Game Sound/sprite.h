#pragma once
#include "component.h"
#include <string>

class Sprite : public Component
{
private:
	std::string m_TexName{};
	float m_X{}, m_Y{};
	float m_Width{}, m_Height{};
	float m_U{}, m_V{};
	float m_UW{}, m_VH{};
	D3DXCOLOR m_Color;
public:
	void Init2D(std::string texName, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void Draw(); 
	
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
};