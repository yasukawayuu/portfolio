#include "main.h"
#include "debug.h"

std::list<std::string> Debug::m_Log{};

void Debug::Draw()
{
	for (std::string log : m_Log)
	{
		ImGui::Text(log.c_str());
	}
	
}
