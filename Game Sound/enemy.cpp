
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mainCamera.h"
#include "animationModel.h"
#include "audio.h"
#include "audioManager.h"
#include "enemy.h"
#include "shader.h"
#include "player.h"


void Enemy::Init()
{


	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\enemy\\slender.fbx");
	m_Model->LoadAnimation("asset\\model\\enemy\\Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\enemy\\Walking.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\enemy\\Walking2.fbx", "Walk2");

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");
	m_Transform->Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_Transform->Position = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
	m_Transform->Rotation = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	m_FootStep = AddComponent<Audio>();
	m_FootStep->SetDataName("footstep");
	m_FootStep->Load(L"asset\\audio\\enemy\\footstep02.wav");
	m_FootStep->Init(AUDIO_3D);
	AudioManager::GetInstance()->AddAudio(m_FootStep->GetData().Name, m_FootStep);

}

void Enemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	GameObject::Uninit();
}



void Enemy::Update()
{
	switch (m_State)
	{
	case ENEMY_STATE_IDLE:
		UpdateIdel();
		break;
	case ENEMY_STATE_MOVE:
		UpdateMove();
		break;
	case ENEMY_STATE_CHASE:
		UpdateChase();
		break;
	default:
		break;
	}

	m_Time++;
	m_BlendRate += 0.1f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;

	
	m_FootStep->SetEmitter(m_Transform->GetForward(), m_Transform->GetUp(), m_Transform->Position, m_Velocity);



	GameObject::Update();
}

void Enemy::Draw()
{
	/*Scene* scene = Manager::GetInstance()->GetScene();
	MainCamera* camera = scene->GetGameObject<MainCamera>();

	if(!camera->CheckView(m_Transform->Position, 1.0f))
		return;*/

	GameObject::Draw();

	

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);


	m_Model->Draw();
}

void Enemy::UpdateIdel()
{

	if (m_NextAnimationName != "Walk")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Walk";
		m_BlendRate = 0.0f;
	}

	m_State = ENEMY_STATE_MOVE;
}

void Enemy::UpdateMove()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f,0.0f,0.0f) - m_Transform->Position;
	m_Transform->Rotation = D3DXVECTOR3(0.0f, atan2f(vec.x, vec.z), 0.0f);
	float len = D3DXVec3Length(&vec);

	if (len > 0.1f)
	{
		m_Transform->Position += m_Transform->GetForward() * 0.01f;

		m_SoundTime += 0.0375f;

		if (m_SoundTime > 1.0f)
		{
			m_SoundTime = 0.0f;
			m_FootStep->Play(false);
		}
	}
	else
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}

		m_NextStateTime++;

		if (m_NextStateTime > 120)
		{
			if (m_NextAnimationName != "Walk2")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Walk2";
				m_BlendRate = 0.0f;
			}
			m_State = ENEMY_STATE_CHASE;
		}		
	}


}

void Enemy::UpdateChase()
{
	Transform* playrPos = Manager::GetInstance()->GetScene()->GetGameObject<Player>()->GetComponent<Transform>();
	D3DXVECTOR3 vec = playrPos->Position - m_Transform->Position;

	m_Transform->Rotation = D3DXVECTOR3(0.0f, atan2f(vec.x, vec.z), 0.0f);

	m_Transform->Position += m_Transform->GetForward() * 0.04f;

	m_SoundTime += 0.04875f;

	if (m_SoundTime > 1.0f)
	{
		m_SoundTime = 0.0f;
		m_FootStep->Play(false);
	}
}

