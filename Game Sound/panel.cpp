
#include "main.h"
#include "renderer.h"
#include "panel.h"
#include "textureManager.h"
#include "shader.h"

void Panel::Init()
{
	AddComponent<Shader>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	
}


void Panel::Update()
{

}

void Panel::Draw()
{

	GameObject::Draw();



	//TextureManager::GetInstance()->Draw3D("siba", 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);


	/*FOG fog;
	fog.FogP.x = 10.0f;
	fog.FogP.y = m_FogEnd;
	fog.FogP.z = 2.0f;
	fog.FogC = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	fog.FogGC = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	renderer->SetFog(fog);*/

}
