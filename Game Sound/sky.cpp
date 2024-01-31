#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "mainCamera.h"
#include "sky.h"
#include "shader.h"
#include "object3D.h"

void Sky::Init()
{
	m_Transform->Scale = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	
	AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	AddComponent<Object3D>()->Init("asset\\model\\sky.obj");
}


void Sky::Update()
{
	Scene *scene = Manager::GetInstance()->GetScene();
	MainCamera *mainCamera = scene->GetGameObject<MainCamera>();
	Transform* mainCameraTransform = mainCamera->GetComponent<Transform>();
	
	D3DXVECTOR3 cameraposition = mainCameraTransform->Position;

	m_Transform->Position = D3DXVECTOR3(cameraposition.x,0.0f, cameraposition.z);

}
