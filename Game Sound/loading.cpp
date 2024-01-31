
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "textureManager.h"
#include "modelManager.h"
#include "sprite.h"
#include "shader.h"
#include "loading.h"
#include "title.h"

void Loading::Init()
{
	m_Loading = AddGameObject<GameObject>(2);
	m_Loading->AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	m_Loading->AddComponent<Sprite>()->Init2D("loading", SCREEN_WIDTH / 2 - 150.0f, SCREEN_HEIGHT / 2 - 200.0f, 300.0f, 400.0f, 0.0f, 0.0f, 1.0f, 1.0f);

}

void Loading::Update()
{
	static float a = 0.0f;
	static float b = 0.03f;

	if (a > 1.0f)
	{
		b *= -1.0f;
	}

	if (a < 0.0f)
	{
		b *= -1.0f;
	}

	a += b;
	m_Loading->GetComponent<Sprite>()->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,a));


	if (TextureManager::GetInstance()->GetLoadFinish())
		Manager::GetInstance()->SetScene<Title>();
}
