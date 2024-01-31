#pragma once

#include "component.h"
#include "transform.h"
#include <list>

class GameObject
{
protected:
	bool m_Destroy = false;
	Transform* m_Transform{};
	D3DXVECTOR3 m_Velocity{};
	std::list<Component*> m_Component{};

public:
	GameObject() { m_Transform = AddComponent<Transform>(); }

	virtual void Init(){}

	virtual void Uninit()
	{
		for (auto *component : m_Component)
		{
			component->Uninit();
		}
	}

	virtual void Update()
	{
		for (auto *component : m_Component)
		{
			component->Update();
		}
	}

	virtual void Draw()
	{
		for (auto *component : m_Component)
		{
			component->Draw();
		}
	}
	

	void SetDestroy(void)
	{
		m_Destroy = true;
	}

	void SetVelocity(D3DXVECTOR3 velocity)
	{
		m_Velocity = velocity;
	}

	D3DXVECTOR3 GetVelocity()
	{
		return m_Velocity;
	}

	bool Destroy(void)
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	//virtual void Init(){}　仮想関数
	//virtual　俺様を継承したやつの関数を呼び出す
	//必ず実装しなくてもいい

	//virtual void Init() = 0;
	//純粋仮想関数は必ず実装しなきゃいけない
	template <typename T>//テンプレート関数 型をかえう
	T* AddComponent()
	{
		Component* component = new T();
		m_Component.push_back(component);
		component->Init();

		return (T*)component;
	}

	template <typename T>//テンプレート関数 型をかえう
	T* GetComponent()
	{

		for (Component* component : m_Component)
		{
			if (typeid(*component) == typeid(T))//型を調べる（RTTI動的型情報）
			{
				return (T*)component;
			}
		}

		return nullptr;
	}
};