
#include "main.h"
#include "renderer.h"
#include "effect.h"
#include "scene.h"
#include "mainCamera.h"
#include "manager.h"
#include "textureManager.h"
#include "player.h"
#include "shader.h"

void Effect::Init()
{
	AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
}


void Effect::Update()
{
	m_Count++;


	if (m_DoTracking)
	{
		m_Transform->Position = D3DXVECTOR3(m_Target->x, m_Target->y, m_Target->z + m_Correction);
	}

	//最後まで描画した消す
	if (m_Count >= (m_U * m_V))
	{
		SetDestroy();
		return;
	}

	m_Transform->Billboard();
}

void Effect::Draw()
{

	GameObject::Draw();

	//テクスチャ
	float x = m_Count % m_U * (1.0f / m_U);
	float y = m_Count / m_V * (1.0f / m_V);

	//TextureManager::GetInstance()->Draw3D("", 1.0f, 1.0f, x, y, 1.0f / m_U, 1.0f / m_V);
}
