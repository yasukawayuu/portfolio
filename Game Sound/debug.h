#pragma once
#include <list>
#include <string>

class Debug
{
private:
	static std::list<std::string> m_Log;
public:
	static void Log(std::string log) { m_Log.push_back(log); }
	static void Draw();
};