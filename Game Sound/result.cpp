#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "sprite.h"
#include "shader.h"
#include "result.h"
#include "input.h"

#include "title.h"
#include "Fade.h"

void Result::Init()
{
	GameObject* title = AddGameObject<GameObject>(2);
	title->AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	title->AddComponent<Sprite>()->Init2D("result", 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	m_Fade = AddGameObject<Fade>(2);
}


void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
		Manager::GetInstance()->SetScene<Title>();
}
