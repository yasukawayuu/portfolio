#pragma once

#include "audio.h"
#include <unordered_map>
#include <string>


class AudioManager
{
private:
	static AudioManager* m_pInstance;
	std::unordered_map<std::string, Audio*> m_Audio{};
	std::unordered_map<unsigned int, Data> m_Data{};
	unsigned int m_Index = 0;
private:
	AudioManager(){};
	~AudioManager(){};

	void Ducking();
	void Interactiv();

public:
	static AudioManager* GetInstance(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new AudioManager();
		}

		return m_pInstance;
	}
	void AddAudio(std::string name,Audio* audio);
	void AddData(const Data &data);
	bool GetSameName(std::string name);
	void Update();
	void Uninit();
	Data Random(int min,int max, std::vector<int> probability);
};