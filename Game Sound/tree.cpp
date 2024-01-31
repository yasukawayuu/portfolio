
#include "main.h"
#include "renderer.h"
#include "tree.h"
#include "scene.h"
#include "camera.h"
#include "manager.h"
#include "textureManager.h"
#include "shader.h"

void Tree::Init()
{
	AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
}


void Tree::Update()
{
	//m_Transform->Billboard();
}

void Tree::Draw()
{
	GameObject::Draw();
	

	TextureManager::GetInstance()->Draw3DLeftTop("grass", 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, 1.0f);
}
