#pragma once

#include "component.h"

class Shader : public Component
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
public:
	void Init(const char* FileNameVS, const char* FileNamePS);
	void Uninit();
	void Draw();
};