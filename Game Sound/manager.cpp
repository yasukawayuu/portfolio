#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "modelManager.h"
#include "textureManager.h"
#include "audioManager.h"
#include "input.h"
#include "cursor.h"
#include "audio.h"
#include "scene.h" 
#include "mainCamera.h"
#include "player.h"
#include "enemy.h"
#include "meshField.h"
#include "box.h"
#include "cylinder.h"
#include "tatami.h"
#include "candleHolder.h"
#include "debug.h"
#include "loading.h"

#include <thread>

#define nameof(x) #x

Manager* Manager::m_pInstance{};

void Manager::Init()
{
	Renderer::GetInstance()->Init();

	Input::Init();
	Audio::InitMaster();

	TextureManager* texture = TextureManager::GetInstance();
	texture->Init();


	std::thread th(&TextureManager::Load, TextureManager::GetInstance());
	th.detach();

	m_PointLight.Position = D3DXVECTOR4(10.0f, 3.0f, 0.0f,1.0f);
	m_PointLight.Attenuation = D3DXVECTOR4(0.1f, 0.1f, 0.1f,1.0f);
	m_PointLight.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_SpotLight.Position = D3DXVECTOR4(0.0f, 3.0f, 0.0f, 1.0f);
	m_SpotLight.Direction = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	D3DXVec4Normalize(&m_SpotLight.Direction, &m_SpotLight.Direction);
	m_SpotLight.Attenuation = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);

	SetScene<Loading>();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	TextureManager::GetInstance()->Unload();
	TextureManager::DeleteInstance();
	ModelManager::DeleteInstance();

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::GetInstance()->Uninit();

}

void Manager::Update()
{
	Input::Update();
	Cursor::Update();

	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}

	if (Input::GetKeyPress('E'))
		m_SpotLight.Position.x += 0.1f;
	if (Input::GetKeyPress('Q'))
		m_SpotLight.Position.x -= 0.1f;

	m_Scene->Update();
}

void Manager::Draw()
{
	
	/*LIGHT light{};
	light.Enable = false;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 lightpos = D3DXVECTOR3(-25.0f, 25.0f, -25.0f);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightpos, &lightTarget, &lightUp);
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 100.0f);

	Renderer::GetInstance()->SetLight(light);

	Renderer::GetInstance()->BeginDepth();

	Renderer::GetInstance()->SetDepthViewport();

	Renderer::GetInstance()->SetViewMatrix(&light.ViewMatrix);
	Renderer::GetInstance()->SetProjectionMatrix(&light.ProjectionMatrix);

	if (m_Scene->GetGameObject<Player>())
	{
		m_Scene->GetGameObject<MeshField>()->Draw();
		m_Scene->GetGameObject<Player>()->Draw();
		m_Scene->GetGameObject<Box>()->Draw();

		m_Scene->GetGameObject<Cylinder>()->Draw();
		AudioManager::GetInstance()->Update();
	}*/
	//if (m_Scene->GetGameObject<MainCamera>())
	//{
	//	std::vector<Tatami*> tatamis = m_Scene->GetGameObjects<Tatami>();

	//	for (Tatami* tatami : tatamis)
	//	{
	//		tatami->Draw();
	//	}

	//	std::vector<Box*> boxs = m_Scene->GetGameObjects<Box>();
	//	for (Box* box : boxs)
	//	{
	//		box->Draw();
	//	}

	//	m_Scene->GetGameObject<CandleHolder>()->Draw();

	//}

	for (int i = 0; i < 6; i++)
	{
		D3DXVECTOR3 position = D3DXVECTOR3(m_PointLight.Position.x, m_PointLight.Position.y, m_PointLight.Position.z);
		D3DXVECTOR3 target[6] = {
			D3DXVECTOR3(m_PointLight.Position.x,  m_PointLight.Position.y - 1.0f, m_PointLight.Position.z),
			D3DXVECTOR3(m_PointLight.Position.x,  m_PointLight.Position.y + 1.0f, m_PointLight.Position.z),
			D3DXVECTOR3(m_PointLight.Position.x - 1.0f,  m_PointLight.Position.y, m_PointLight.Position.z),
			D3DXVECTOR3(m_PointLight.Position.x + 1.0f,  m_PointLight.Position.y, m_PointLight.Position.z),
			D3DXVECTOR3(m_PointLight.Position.x,  m_PointLight.Position.y, m_PointLight.Position.z - 1.0f),
			D3DXVECTOR3(m_PointLight.Position.x,  m_PointLight.Position.y, m_PointLight.Position.z + 1.0f),
		};
		D3DXVECTOR3 up[6] = {
			D3DXVECTOR3(1.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 1.0f, 0.0f),
			D3DXVECTOR3(0.0f, 1.0f, 0.0f),
			D3DXVECTOR3(0.0f, 1.0f, 0.0f),
			D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		};

		D3DXMatrixLookAtLH(&m_PointLight.ViewMatrix[i], &position, &target[i], &up[i]);
		D3DXMatrixPerspectiveFovLH(&m_PointLight.ProjectionMatrix, D3DX_PI / 2.0f, (float)SCREEN_WIDTH  / SCREEN_HEIGHT, 0.2f, 25.0f);

		Renderer::GetInstance()->SetPointLight(m_PointLight);
		Renderer::GetInstance()->BeginDepthPoint(i);

		Renderer::GetInstance()->SetDepthViewport();

		Renderer::GetInstance()->SetViewMatrix(&m_PointLight.ViewMatrix[i]);
		Renderer::GetInstance()->SetProjectionMatrix(&m_PointLight.ProjectionMatrix);

		if (m_Scene->GetGameObject<Player>())
		{
			m_Scene->GetGameObject<MeshField>()->Draw();
			//m_Scene->GetGameObject<Enemy>()->Draw();
			//m_Scene->GetGameObject<Player>()->Draw();
			//m_Scene->GetGameObject<Box>()->Draw();

			//m_Scene->GetGameObject<Cylinder>()->Draw();
			AudioManager::GetInstance()->Update();
		}

		/*if (m_Scene->GetGameObject<MainCamera>())
		{
			std::vector<Tatami*> tatamis = m_Scene->GetGameObjects<Tatami>();

			for (Tatami* tatami : tatamis)
			{
				tatami->Draw();
			}

			std::vector<Box*> boxs = m_Scene->GetGameObjects<Box>();
			for (Box* box : boxs)
			{
				box->Draw();
			}

			m_Scene->GetGameObject<CandleHolder>()->Draw();

		}*/
	}

	D3DXVECTOR3 position = D3DXVECTOR3(m_SpotLight.Position.x, m_SpotLight.Position.y, m_SpotLight.Position.z);
	D3DXVECTOR3 target = D3DXVECTOR3(m_SpotLight.Position.x,m_SpotLight.Position.y -1.0f, m_SpotLight.Position.z);
	D3DXVECTOR3 up = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_SpotLight.ViewMatrix, &position, &target, &up);
	D3DXMatrixPerspectiveFovLH(&m_SpotLight.ProjectionMatrix, D3DX_PI / 2.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.2f, 25.0f);
	Renderer::GetInstance()->SetSpotLight(m_SpotLight);
	Renderer::GetInstance()->BeginDepthSpot();
	Renderer::GetInstance()->SetDepthViewport();
	Renderer::GetInstance()->SetViewMatrix(&m_SpotLight.ViewMatrix);
	Renderer::GetInstance()->SetProjectionMatrix(&m_SpotLight.ProjectionMatrix);
	if (m_Scene->GetGameObject<Player>())
	{
		m_Scene->GetGameObject<MeshField>()->Draw();
		//m_Scene->GetGameObject<Enemy>()->Draw();
		//m_Scene->GetGameObject<Box>()->Draw();

		//m_Scene->GetGameObject<Cylinder>()->Draw();
		//AudioManager::GetInstance()->Update();
	}
	/*if (m_Scene->GetGameObject<MainCamera>())
	{
		std::vector<Tatami*> tatamis = m_Scene->GetGameObjects<Tatami>();

		for (Tatami* tatami : tatamis)
		{
			tatami->Draw();
		}

		std::vector<Box*> boxs = m_Scene->GetGameObjects<Box>();
		for (Box* box : boxs)
		{
			box->Draw();
		}

		m_Scene->GetGameObject<CandleHolder>()->Draw();

	}*/


	Renderer::GetInstance()->Begin();

	Renderer::GetInstance()->SetDefaultViewport();

	
	Renderer::GetInstance()->SetDepthSamplerState();

	m_Scene->Draw();

	if (m_Gui)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowSize(ImVec2(400.0f, 400.0f));
		if (ImGui::Begin("Hierarchie"))
		{
			const type_info& id = typeid(*m_Scene);
			std::string className = id.name();
			if (className.find("class ") == 0)
			{
				className = className.substr(6);
			}
			if (ImGui::CollapsingHeader(className.c_str()))
			{
				static int selected = -1;
				int n = 0;
				for (int i = 0; i < 3; i++)
				{
					for (auto* gameObject : m_Scene->GetGameObejctList(i))
					{
						const type_info& id = typeid(*gameObject);
						std::string className = id.name();

						if (className.find("class ") == 0)
							className = className.substr(6);

						n += 1;
						if (ImGui::Selectable(className.c_str(), selected == n))
							selected = n;
					}
				}

			}
			ImGui::Separator();
		}ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(400.0f, 400.0f));
		if (ImGui::Begin("Inspector"))
		{
			ImGui::InputText("GameObejctName", (char*)nameof(Box), 256);
			if (ImGui::CollapsingHeader("Transform"))
			{
				Transform* BoxTransform = m_Scene->GetGameObject<Box>()->GetComponent<Transform>();
				ImGui::DragFloat3("Box.Position", &BoxTransform->Position->x, 0.1f, -1000.0f, 1000.0f, "%.3f");
				ImGui::DragFloat3("Box.Rotation", &BoxTransform->Rotation->x, 0.1f, -D3DX_PI, D3DX_PI, "%.3f");
				ImGui::DragFloat3("Box.Scale", &BoxTransform->Scale->x, 0.01f, 0.01f, 0.1f, "%.3f");

			}

			if (ImGui::CollapsingHeader("Length"))
			{
				Transform* playerTransform = m_Scene->GetGameObject<Player>()->GetComponent<Transform>();
				Transform* boxTransform = m_Scene->GetGameObject<Box>()->GetComponent<Transform>();
				D3DXVECTOR3 vec = boxTransform->Position - playerTransform->Position;
				float length = D3DXVec3Length(&vec);
				ImGui::DragFloat("Player.Position", &length, 0.1f, -1000.0f, 1000.0f, "%.3f");

			}
			ImGui::Separator();
		}ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(1000.0f, 200.0f));
		if (ImGui::Begin("Log"))
		{
			Debug::Draw();
		}ImGui::End();

		

		ImGui::Render();

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}



	Renderer::GetInstance()->End();


}
