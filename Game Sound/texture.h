#pragma once

class Texture
{
private:
	ID3D11ShaderResourceView* m_Texture = nullptr; 
public:
	
	void Load(const char* textureName);
	void Unload();
	ID3D11ShaderResourceView * GetTexture();
};