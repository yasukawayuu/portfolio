#pragma once
//class Scene; //前方宣言　ポインタ変数以外は無理
#include "scene.h"
#include "renderer.h"

class Manager
{
private:
	static Manager* m_pInstance;
	Scene* m_Scene{};
	Scene* m_NextScene{};
	bool m_Gui = true;
	POINTLIGHT m_PointLight{};
	SPOTLIGHT m_SpotLight{};
private:
	Manager() {};
	~Manager() {};
public:
	static Manager* GetInstance(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new Manager();
		}

		return m_pInstance;
	}

	static void DeleteInstance(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetGui(bool gui) { m_Gui = gui; }
	Scene* GetScene() const { return m_Scene; }

	template<typename T>
	void SetScene()
	{
		m_NextScene = new T();
	}

};