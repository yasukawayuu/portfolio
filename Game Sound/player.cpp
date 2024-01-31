
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "animationModel.h"
#include "audioManager.h"

#include "input.h"
#include "cursor.h"
#include "scene.h"
#include "result.h"
#include "player.h"
#include "enemy.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "meshField.h"
#include "shader.h"
#include "mainCamera.h"
#include "debug.h"

#define STRING(num) #num

void Player::Init()
{

	/*m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Bot.fbx");
	m_Model->LoadAnimation("asset\\model\\Bot_Run.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\Bot_Idle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";*/

	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");

	m_Serif = AddComponent<Audio>();
	m_Serif->SetDataName("serif");
	m_Serif->Load(L"asset\\audio\\Serif\\ano_01.wav");
	m_Serif->Load(L"asset\\audio\\Serif\\watashi_01.wav");
	m_Serif->Load(L"asset\\audio\\Serif\\anataga_01.wav");
	m_Serif->Load(L"asset\\audio\\Serif\\zuttosukidatta_01.wav");
	m_Serif->Load(L"asset\\audio\\Serif\\ehehe_01.wav");
	m_Serif->Load(L"asset\\audio\\Serif\\usouso_02.wav");
	m_Serif->Load(L"asset\\audio\\Serif\\joudandayo_01.wav");
	AudioManager::GetInstance()->AddAudio(m_Serif->GetData().Name, m_Serif);

	m_HeartBeat = AddComponent<Audio>();
	m_HeartBeat->SetDataName("heartbeat");
	m_HeartBeat->Load(L"asset\\audio\\HeartBeat-1shot.wav");
	AudioManager::GetInstance()->AddAudio(m_HeartBeat->GetData().Name, m_HeartBeat);

	m_Transform->Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
}

void Player::Uninit()
{
	 

	GameObject::Uninit();
}

void Player::Update()
{
	GameObject::Update();

	Scene* scene = Manager::GetInstance()->GetScene();
	D3DXVECTOR3 oldPosition = m_Transform->Position;

	/*if (Input::GetKeyPress('W'))
	{
		m_Position.z += 0.1f;
	}

	if (Input::GetKeyPress('S'))
	{
		m_Position.z -= 0.1f;
	}

	if (Input::GetKeyPress('A'))
	{
		m_Position.x -= 0.1f;
	}

	if (Input::GetKeyPress('D'))
	{
		m_Position.x += 0.1f;
	}*/

	if (Input::GetKeyPress('X'))
	{
		m_Serif->Play(false);
	}
	if (Input::GetKeyPress('V'))
	{
		
	}
	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;

	default:
		break;
	}


	m_Transform->Rotation->y = Cursor::GetCursorPosition().x;


	//重力
	m_Velocity.y -= 0.015f;

	//移動
	m_Transform->Position += m_Velocity;

	m_Velocity.x = 0.0f;
	m_Velocity.z = 0.0f;
	//障害物との衝突判定
	float groundHeight = 0.0f;

	MeshField* meshField = scene->GetGameObject<MeshField>();

	groundHeight = meshField->GetHeight(m_Transform->Position);

	/*Enemy* enemy = scene->GetGameObject<Enemy>();
	D3DXVECTOR3 enemyPos = enemy->GetComponent<Transform>()->Position;
	D3DXVECTOR3 vec = enemyPos - m_Transform->Position;
	float len = D3DXVec3Length(&vec);*/



	/*if (len > 10.0f && enemy->GetState() == ENEMY_STATE_CHASE)
	{
		m_SoundTime += 0.02f;
		m_HeartBeat->SetVolume(0.1f);
	}

	if(len < 10.0f && len > 6.0f && enemy->GetState() == ENEMY_STATE_CHASE)
	{
		m_SoundTime += 0.04f;
		m_HeartBeat->SetVolume(0.2f);
	}

	if (len < 6.0f && enemy->GetState() == ENEMY_STATE_CHASE)
	{
		m_SoundTime += 0.06f;
		m_HeartBeat->SetVolume(0.4f);
	}

	if (len < 2.0f && enemy->GetState() == ENEMY_STATE_CHASE)
	{
		Manager::GetInstance()->SetScene<Result>();
	}

	
	if (m_SoundTime > 1.0f)
	{
		m_SoundTime = 0.0f;
		m_HeartBeat->Play(false);
	}*/

	

	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();

	for (Cylinder* cylinder : cylinders)
	{
		Transform* cylinderTransform = cylinder->GetComponent<Transform>();
		D3DXVECTOR3 position = cylinderTransform->Position;
		D3DXVECTOR3 scale = cylinderTransform->Scale;

		D3DXVECTOR3 direction = m_Transform->Position - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);


		if (length < scale.x + 0.5f)
		{
			if (m_Transform->Position->y < position.y + scale.y - 0.5f)
			{
				m_Transform->Position->x = oldPosition.x;
				m_Transform->Position->z = oldPosition.z;

			}
			else
			{
				groundHeight = position.y + scale.y;
			}

			break;
		}
	}

	std::vector<Box*> boxes = scene->GetGameObjects<Box>();

	for (Box* box : boxes)
	{
		Transform* boxTransform = box->GetComponent<Transform>();
		D3DXVECTOR3 position = boxTransform->Position;
		D3DXVECTOR3 scale = boxTransform->Scale;
		D3DXVECTOR3 right = boxTransform->GetRight(); // X分離軸
		D3DXVECTOR3 forward = boxTransform->GetForward(); //Z分離軸
		D3DXVECTOR3 direction = m_Transform->Position - position;//直方体からプレイヤーまでの方向ベクトル

		//float Length = D3DXVec3Length(&direction);

		float obbx = D3DXVec3Dot(&direction, &right);
		float obbz = D3DXVec3Dot(&direction, &forward);
		//OBB
		if (fabs(obbx) < scale.x )
			if (fabs(obbz) < scale.z)
			{
				if (m_Transform->Position->y < position.y + scale.y * 2.0f - 0.5f)
				{
					m_Transform->Position->x = oldPosition.x;
					m_Transform->Position->z = oldPosition.z;
					Debug::Log("hit");
				}
				else
				{
					groundHeight = position.y + scale.y * 2.0f;
				}

				break;;
			}

		//AABB
		/*float BoxXmin = position.x - scale.x;
		float BoxXmax = position.x + scale.x;
		float BoxZmin = position.z - scale.z;
		float BoxZmax = position.z + scale.z;

		if (BoxXmax > m_Transform->Position->x)
			if (BoxXmin < m_Transform->Position->x)
				if (BoxZmax > m_Transform->Position->z)
					if (BoxZmin < m_Transform->Position->z)
					{
						if (m_Transform->Position->y < position.y + scale.y * 2.0f - 0.5f)
						{
							m_Transform->Position->x = oldPosition.x;
							m_Transform->Position->z = oldPosition.z;
							Debug::Log("hit");
						}
						else
						{
							groundHeight = position.y + scale.y * 2.0f;
						}

						break;

					}*/

	}

	//接地
	if (m_Transform->Position->y <= groundHeight && m_Velocity.y < 0.0f)
	{
		m_Transform->Position->y = groundHeight;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
	}

}

void Player::Draw()
{
	/*Scene* scene = Manager::GetInstance()->GetScene();
	MainCamera* camera = scene->GetGameObject<MainCamera>();

	if(!camera->CheckView(m_Transform->Position, 1.0f))
		return;*/

	GameObject::Draw();

	return;

	/*m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);

	m_Time++;
	m_BlendRate += 0.1f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;


	m_Model->Draw();*/
}

void Player::UpdateGround()
{
	//bool move = false;

	//サードパーソンビュー
	if (Input::GetKeyPress('W'))
	{
		/*if (m_NextAnimationName != "Run")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Run";
			m_BlendRate = 0.0f;
		}*/
		m_Velocity = m_Transform->GetForward() * 0.1f;
		//move = true;
	}

	if (Input::GetKeyPress('S'))
	{
		m_Velocity = -m_Transform->GetForward() * 0.1f;
	}

	/*if (move == false)
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}*/

	if (Input::GetKeyPress('A'))
	{
		m_Velocity = -m_Transform->GetRight() * 0.1f;
	}

	if (Input::GetKeyPress('D'))
	{
		m_Velocity = m_Transform->GetRight() * 0.1f;
	}
	//斜め移動が速度速い



	if (Input::GetKeyTrigger('J'))
	{
		m_IsGround = false;
		m_Velocity.y = 0.35f;
		m_PlayerState = PLAYER_STATE_JUMP;
	}

	
}

void Player::UpdateJump()
{
	if (m_IsGround == true)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

//爆発エフェクト完成ができたら・・・
//・爆発アニメーション自作
//・木のビルボード作成
//・コインなどのアイテム作成