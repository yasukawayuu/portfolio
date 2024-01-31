#include "main.h"
#include "renderer.h"
#include "object3D.h"
#include "modelManager.h"

void Object3D::Init(const char* FileName)
{
	m_DrawIndex = ModelManager::GetInstance()->Load(FileName);
}

void Object3D::Draw()
{
	ID3D11ShaderResourceView* depthshadowTexture = Renderer::GetInstance()->GetDepthShadowTexture();
	Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(1, 1, &depthshadowTexture);

	for (int i = 0; i < 6; i++)
	{
		ID3D11ShaderResourceView* depthshadowTexture2 = Renderer::GetInstance()->GetDepthPointShadowTexture(i);
		Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(i + 2, 1, &depthshadowTexture2);
	}

	ID3D11ShaderResourceView* depthshadowTexture3 = Renderer::GetInstance()->GetDepthSpotShadowTexture();
	Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(8, 1, &depthshadowTexture3);

	ModelManager::GetInstance()->Draw(m_DrawIndex);
}
