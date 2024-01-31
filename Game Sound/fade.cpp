#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "textureManager.h"
#include "shader.h"
#include "sprite.h"

void Fade::Init()
{

	AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init2D("fade", 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
}


void Fade::Update()
{
	GameObject::Update();

	if (!m_FadeOut)
	{
		m_a -= 0.01f;
		if (m_a < 0.0f)
		{
			m_a = 0.0f;
		}
	}
	else
	{
		m_a += 0.01f;
		if (m_a > 1.0f)
		{
			m_a = 1.0f;
			m_FadeFinish = true;
		}
			
	}
	
	m_Sprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));
}