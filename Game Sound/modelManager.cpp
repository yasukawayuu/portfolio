
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "modelManager.h"

ModelManager* ModelManager::m_pInstance{};

unsigned int ModelManager::Load(const char* FileName)
{
	for (unsigned int i = 0; i < m_Index; i++)
	{
		if (m_Model[i]->GetFileName() == FileName)
		{
			return i;
		}
	}

	m_Model[m_Index] = new Model();
	m_Model[m_Index]->Load(FileName);
	m_Index++;
	return m_Index - 1;

}

void ModelManager::Unload()
{
	for (auto model : m_Model)
	{
		model.second->Unload();
		delete model.second;
	}

	m_Model.clear();

	m_Index = 0;
}

void ModelManager::Draw(unsigned int Index)
{
	m_Model[Index]->Draw();
}

