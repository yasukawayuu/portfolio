#include "main.h"
#include "renderer.h"
#include "texture.h"



void Texture::Load(const char * textureName)
{
	Renderer* renderer = Renderer::GetInstance();

	//テクスチャの読み込み
	D3DX11CreateShaderResourceViewFromFile(renderer->GetDevice(),
		textureName,
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);
}

void Texture::Unload()
{
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return m_Texture;
}
