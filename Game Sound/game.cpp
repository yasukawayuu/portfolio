
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "title.h"
#include "input.h"

#include "shader.h"
#include "object3D.h"

#include "audio.h"
#include "audioManager.h"
#include "sprite.h"

#include "mainCamera.h"
#include "panel.h"
#include "meshField.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "cylinder.h"
#include "box.h"
#include "result.h"
#include "sky.h"
#include "fade.h"
#include "tree.h"

#include <random>

void Game::Init()
{

	AddGameObject<MainCamera>(0); //関数生成される
	//AddGameObject<Sky>(1);
	MeshField* meshfield = AddGameObject<MeshField>(1);
	Player* player = AddGameObject<Player>(1);
	player->GetComponent<Transform>()->Position = D3DXVECTOR3(0.0f,0.0f,-3.0f);
	//AddGameObject<Child>(1)->SetParent(player);

	//m_Enemy = AddGameObject<Enemy>(1);
	
	//Cylinder *cylinder = AddGameObject<Cylinder>(1);
	//Transform* cylinderTransform = cylinder->GetComponent<Transform>();
	//cylinderTransform->Position = (D3DXVECTOR3(3.0f, 0.0f, 3.0f));
	//cylinderTransform->Scale = (D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	
	//cylinder = AddGameObject<Cylinder>(1);
	//Transform* cylinderTransform2 = cylinder->GetComponent<Transform>();
	//cylinderTransform2->Position = (D3DXVECTOR3(6.0f, 0.0f, 3.0f));
	//cylinderTransform2->Scale = (D3DXVECTOR3(3.0f, 3.0f,3.0f));
	
	/*Box *box = AddGameObject<Box>(1);
	Transform* boxTransform = box->GetComponent<Transform>();
	boxTransform->Position = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	boxTransform->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boxTransform->Scale = (D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	D3DXVECTOR3 vec = boxTransform->Position - D3DXVECTOR3(0.0f, 0.0f, -3.0f);*/


	std::random_device rd; //乱数生成器の作成
	std::mt19937 mt(rd()); //メル11センヌ・ツイスター
	std::uniform_real_distribution<float> xz(-45.0f, 45.0f);//小数の乱数

	/*GameObject* n = AddGameObject<GameObject>(2);
	n->AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	n->AddComponent<Sprite>()->Init2D("", 0.0f, 0.0f, 300.0f, 300.0f, 0.0f, 0.0f, 1.0f, 1.0f);*/

	m_Fade = AddGameObject<Fade>(2);

	m_BGM = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_BGM->SetDataName("bgm");
	m_BGM->Load(L"asset\\audio\\Serif\\genjitsunosukima.mp3");
	m_BGM->SetVolume(0.1f);
	m_BGM->Play(true);
	AudioManager::GetInstance()->AddAudio(m_BGM->GetData().Name, m_BGM);

	m_BGM1 = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_BGM1->SetDataName("bgm1");
	m_BGM1->Load(L"asset\\audio\\Horror-NeverLookBack_loop.m4a");
	m_BGM1->SetVolume(0.1f);
	AudioManager::GetInstance()->AddAudio(m_BGM1->GetData().Name, m_BGM1);
}

void Game::Update()
{
	

	Scene::Update();	

	/*if(m_Enemy->GetState() == ENEMY_STATE_CHASE && m_BGM1->GetSoundEnd())
		m_BGM1->Play(true);*/



	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
		Manager::GetInstance()->SetScene<Result>();

	
}
