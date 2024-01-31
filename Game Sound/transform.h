#pragma once
#include "component.h"
#include "property.h"

class Transform : public Component
{
private:
	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMATRIX m_Rot{};
	bool Look = false;
public:
	Property<D3DXVECTOR3> Position{ m_Position };
	Property<D3DXVECTOR3> Rotation{ m_Rotation };
	Property<D3DXVECTOR3> Scale{ m_Scale };

	/*void SetPosition(D3DXVECTOR3 position) { m_Position = position; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	void SetRotation(D3DXVECTOR3 rotation) { m_Rotation = rotation; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }
	D3DXVECTOR3 GetScale(void) { return m_Scale; }*/

	D3DXVECTOR3 GetForward(void)
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight(void)
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 Right;
		Right.x = rot._11;
		Right.y = rot._12;
		Right.z = rot._13;

		return Right;
	}

	D3DXVECTOR3 GetUp(void)
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 Up;
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;

		return Up;
	}
	
	void Draw();
	void Billboard();
};
