#include "main.h"
#include "manager.h"
#include "input.h"
#include "audio.h"
#include "audioManager.h"
#include "box.h"
#include "fade.h"
#include <random>
#include <vector>

AudioManager* AudioManager::m_pInstance{};



Data AudioManager::Random(int min,int max,std::vector<int> probability)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::vector<int> num{};
	
	for (int i = min; i <= max; i++)
	{
		num.push_back(i);
	}

	std::discrete_distribution<> weighted_dist{probability.begin(),probability.end()};

	return m_Data[num[weighted_dist(mt)]];
}


void AudioManager::Ducking()
{
	//Fade* fade = Manager::GetInstance()->GetScene()->GetGameObject<Fade>();
	/*for (auto audio : m_Audio)
	{
		audio.second->FadeVolume();
	}*/

	/*if (!m_Audio["serif"]->GetSoundEnd())
	{
		m_Audio["bgm"]->FadeVolume(0.1f);
	}
	else
	{
		m_Audio["bgm"]->FadeVolume(1.0f);
	}*/
}

void AudioManager::Interactiv()
{

}

void AudioManager::AddAudio(std::string name,Audio* audio)
{
	m_Audio[name] = new Audio;
	m_Audio[name] = audio;
	
	for (unsigned int i = 0; i < m_Index; i++)
	{
		if (m_Data[i].Name == m_Audio[name]->GetData().Name)
		{
			m_Audio[name]->SetData(m_Data[i]);
			return;
		}
	}

	m_Data[m_Index] = m_Audio[name]->GetData();
	m_Audio[name]->SetIndex(m_Index);
	m_Index++;
}

void AudioManager::AddData(const Data &data)
{
	for (unsigned int i = 0; i < m_Index; i++)
	{
		if (m_Data[i].Name == data.Name)
		{
			return;
		}
	}

	m_Data[m_Index] = data;
	m_Index++;
}

bool AudioManager::GetSameName(std::string name) 
{
	for (unsigned int i = 0; i < m_Index; i++)
	{
		if (m_Data[i].Name == name)
		{
			return true;
		}
	}

	return false;
}

void AudioManager::Update()
{
	Interactiv();
	Ducking();
}

void AudioManager::Uninit()
{
	for (auto audio : m_Audio)
	{
		delete audio.second;
	}

	m_Audio.clear();

	for (auto data : m_Data)
	{
		data.second.SourceVoice->DestroyVoice();
	}

	m_Data.clear();

	m_Index = 0;
}


