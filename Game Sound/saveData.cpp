#include "saveData.h"

SaveData* SaveData::m_pInstance{};

void SaveData::Save(int num)
{
	fout.open("savedata\\file.data", std::ios::out | std::ios::binary | std::ios::trunc);
	fout.write(reinterpret_cast<const char*>(&num), sizeof(num));
	fout.close();
}

int SaveData::LoadSave(void)
{
	fin.open("savedata\\file.data", std::ios::in | std::ios::binary);
	int n;
	fin.read((char*)&n, sizeof(n));
	fin.close();
	return n;
}
