#pragma once

class Model;
#include <unordered_map>
#include <string>

class ModelManager
{
private:
	static ModelManager* m_pInstance;
	std::unordered_map<unsigned int, Model*> m_Model;
	unsigned int m_Index{};
private:
	ModelManager() {};
	~ModelManager() {};
public:
	static ModelManager* GetInstance(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new ModelManager();
		}

		return m_pInstance;
	}

	static void DeleteInstance(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	unsigned int Load(const char* FileName);
	void Unload();
	void Draw(unsigned int Index);


};