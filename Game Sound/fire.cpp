#include "main.h"
#include "renderer.h"
#include "fire.h"
#include "shader.h"
#include "particle.h"


void Fire::Init()
{
	AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	AddComponent<Particle>();
	m_Transform->Position = D3DXVECTOR3(0.0f, 1.8f, 0.0f);
}

void Fire::Update()
{
	GameObject::Update();
	m_Transform->Billboard();
}
