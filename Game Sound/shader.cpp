#include "main.h"
#include "renderer.h"
#include "shader.h"

void Shader::Init(const char* FileNameVS, const char* FileNamePS)
{
	Renderer* renderer = Renderer::GetInstance();

	renderer->CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		FileNameVS);

	renderer->CreatePixelShader(&m_PixelShader,
		FileNamePS);
}

void Shader::Uninit()
{
	if (m_VertexLayout != NULL)
	{
		m_VertexLayout->Release();
		m_VertexLayout = NULL;
	}

	if (m_VertexShader != NULL)
	{
		m_VertexShader->Release();
		m_VertexShader = NULL;
	}

	if (m_PixelShader != NULL)
	{
		m_PixelShader->Release();
		m_PixelShader = NULL;
	}
}


void Shader::Draw()
{
	Renderer* renderer = Renderer::GetInstance();
	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	renderer->GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
}
