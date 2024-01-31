#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Transform.h"
#include "mainCamera.h"

void Transform::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	if(!Look)
	D3DXMatrixRotationYawPitchRoll(&m_Rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * m_Rot * trans;
	Renderer::GetInstance()->SetWorldMatrix(&world);
}

void Transform::Billboard()
{
	//カメラのビューマトリクス　どこ見てるどこを向いてるかの情報
	MainCamera* mainCamera = Manager::GetInstance()->GetScene()->GetGameObject<MainCamera>();
	D3DXMATRIX view = mainCamera->GetViewMatrix();

	//ビューの逆行列
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view); //逆行列
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	m_Rot = invView;
	Look = true;
}
