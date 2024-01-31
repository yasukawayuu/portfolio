
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "audioManager.h"
#include "box.h"
#include "shader.h"
#include "object3D.h"
#include "audio.h"

void Box::Init()
{
	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");
	AddComponent<Object3D>()->Init("asset\\model\\wash\\box.obj");

	m_WaterDrop = AddComponent<Audio>();
	m_WaterDrop->SetDataName("water");
	m_WaterDrop->Load(L"asset\\audio\\water_drop_00.mp3");
	m_WaterDrop->Init(AUDIO_3D);
	
	AudioManager::GetInstance()->AddAudio(m_WaterDrop->GetData().Name, m_WaterDrop);

	Audio water1{};
	water1.SetDataName("water1");
	water1.Load(L"asset\\audio\\water_drop_01.mp3");

	AudioManager::GetInstance()->AddData(water1.GetData());

	Audio water2{};
	water2.SetDataName("water2");
	water2.Load(L"asset\\audio\\water_drop_02.mp3");

	AudioManager::GetInstance()->AddData(water2.GetData());

	Audio water3{};
	water3.SetDataName("water3");
	water3.Load(L"asset\\audio\\water_drop_03.mp3");

	AudioManager::GetInstance()->AddData(water3.GetData());

	Audio water4{};
	water4.SetDataName("water4");
	water4.Load(L"asset\\audio\\water_drop_04.mp3");

	AudioManager::GetInstance()->AddData(water4.GetData());

	Audio water5{};
	water5.SetDataName("water5");
	water5.Load(L"asset\\audio\\water_drop_05.mp3");

	AudioManager::GetInstance()->AddData(water5.GetData());

	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Box::Update()
{
	m_WaterDrop->SetEmitter(m_Transform->GetForward(), m_Transform->GetUp(), m_Transform->Position, m_Velocity);

	if (Input::GetKeyTrigger('Z'))
	{
		m_WaterDrop->SetData(AudioManager::GetInstance()->Random(m_WaterDrop->GetIndex(), m_WaterDrop->GetIndex() + 5, m_Probability));
		m_WaterDrop->Play(false);
	}

	GameObject::Update();
}


void Box::Draw()
{
	GameObject::Draw();
	
	
}
