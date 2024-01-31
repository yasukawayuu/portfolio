#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "textureManager.h"


void Sprite::Init2D(std::string texName, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color)
{
	m_TexName = texName;
	m_X = X;
	m_Y = Y;
	m_Width = Width;
	m_Height = Height;
	m_U = U;
	m_V = V;
	m_UW = UW;
	m_VH = VH;
	m_Color = color;
}



void Sprite::Draw()
{
	TextureManager::GetInstance()->Draw2D(m_TexName,m_X,m_Y,m_Width,m_Height,m_U,m_V,m_UW,m_VH,m_Color);
}
