#pragma once

#include <fstream>

class SaveData
{
private:
	static SaveData* m_pInstance;
	std::ofstream fout;
	std::ifstream fin;
private:
	SaveData() {};
	~SaveData() {};
public:
	static SaveData* GetInstance(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new SaveData;
		}

		return m_pInstance;
	}

	static void DeleteInstance(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void Save(int num);
	int LoadSave(void);
};