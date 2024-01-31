
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "meshField.h"
#include "mainCamera.h"
#include "sprite.h"
#include "shader.h"
#include "title.h"
#include "input.h"

#include "game.h"
#include "box.h"
#include "tree.h"
#include "tatami.h"
#include "candleHolder.h"
#include "fire.h"
#include "fade.h"


void Title::Init()
{
	AddGameObject<MainCamera>(0)->GetComponent<Transform>()->Position = D3DXVECTOR3(0.0f, 3.0f, -20.0f);

	/*MeshField* meshfield = AddGameObject<MeshField>(1);
	Box* box = AddGameObject<Box>(1);
	box->GetComponent<Transform>()->Position = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
	box->GetComponent<Transform>()->Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	box = AddGameObject<Box>(1);
	box->GetComponent<Transform>()->Position = D3DXVECTOR3(0.0f, 2.0f, 2.0f);
	box->GetComponent<Transform>()->Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	box = AddGameObject<Box>(1);
	box->GetComponent<Transform>()->Position = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
	box->GetComponent<Transform>()->Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	box = AddGameObject<Box>(1);
	box->GetComponent<Transform>()->Position = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	box->GetComponent<Transform>()->Scale = D3DXVECTOR3(0.5f, 10.0f, 6.0f);

	box = AddGameObject<Box>(1);
	box->GetComponent<Transform>()->Position = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
	box->GetComponent<Transform>()->Scale = D3DXVECTOR3(0.5f, 10.0f, 6.0f);

	box = AddGameObject<Box>(1);
	box->GetComponent<Transform>()->Position = D3DXVECTOR3(0.0f, 0.0f, 6.0f);
	box->GetComponent<Transform>()->Scale = D3DXVECTOR3(6.0f, 10.0f, 0.5f);*/

	/*GameObject* null = AddGameObject<GameObject>(1);
	Transform* nulltrans = null->GetComponent<Transform>();

	Transform* tatamitrans;
	Tatami* tatami = AddGameObject<Tatami>(1);
	tatami->GetComponent<Transform>()->Position = D3DXVECTOR3(nulltrans->Position->x - 0.85f, nulltrans->Position->y + 0.0f, nulltrans->Position->z + 0.0f);

	tatami = AddGameObject<Tatami>(1);
	tatami->GetComponent<Transform>()->Position = D3DXVECTOR3(nulltrans->Position->x + 0.85f, nulltrans->Position->y + 0.0f, nulltrans->Position->z + 0.0f);

	tatami = AddGameObject<Tatami>(1);
	tatamitrans = tatami->GetComponent<Transform>();
	tatamitrans->Position = D3DXVECTOR3(nulltrans->Position->x - 2.55f, nulltrans->Position->y + 0.0f, nulltrans->Position->z + 0.0f);
	tatamitrans->Scale = D3DXVECTOR3(1.0f,1.0f,2.0f);

	tatami = AddGameObject<Tatami>(1);
	tatamitrans = tatami->GetComponent<Transform>();
	tatamitrans->Position = D3DXVECTOR3(nulltrans->Position->x + 2.55f, nulltrans->Position->y + 0.0f, nulltrans->Position->z + 0.0f);
	tatamitrans->Scale = D3DXVECTOR3(1.0f, 1.0f, 2.0f);

	tatami = AddGameObject<Tatami>(1);
	tatamitrans = tatami->GetComponent<Transform>();
	tatamitrans->Position = D3DXVECTOR3(nulltrans->Position->x + 0.0f, nulltrans->Position->y + 0.0f, nulltrans->Position->z + 2.55f);
	tatamitrans->Rotation = D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f);

	tatami = AddGameObject<Tatami>(1);
	tatamitrans = tatami->GetComponent<Transform>();
	tatamitrans->Position = D3DXVECTOR3(nulltrans->Position->x + 0.0f, nulltrans->Position->y + 0.0f, nulltrans->Position->z - 2.55f);
	tatamitrans->Rotation = D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f);*/

	AddGameObject<CandleHolder>(1)->GetComponent<Transform>()->Position = D3DXVECTOR3(0.0f,0.09f,0.0f);
	
	//AddGameObject<Tree>(2);
	AddGameObject<Fire>(2);

	/*GameObject* n = AddGameObject<GameObject>(2);
	n->AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	n->AddComponent<Sprite>()->Init2D("", 0.0f, 0.0f, 300.0f, 300.0f, 0.0f, 0.0f, 1.0f, 1.0f);*/
	m_BGM = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_BGM->SetDataName("bgm");
	m_BGM->LoadSoundFile(L"asset\\audio\\Serif\\genjitsunosukima.mp3");
	m_BGM->SetVolume(0.1f);
	AudioManager::GetInstance()->AddAudio(m_BGM->GetData().Name, m_BGM);

	m_Fade = AddGameObject<Fade>(2);

}

void Title::Update()
{
	Scene::Update();
	m_BGM->PlayStreaming();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
		Manager::GetInstance()->SetScene<Game>();
}
