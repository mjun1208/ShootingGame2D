#pragma once
#include "singleton.h"


class cMapManager : public singleton<cMapManager>
{
private:
	vector<cTile*> mapCode;
public:
	cMapManager();
	virtual ~cMapManager();

	void AddInfo(int _x, UINT _y, UINT _form);
	void Sort();
	void SaveInfo(int Stage);
	void LoadInfo(int Map);

	void Release();

	vector<cTile*>& OutInfo();
};

#define MapSet cMapManager::GetInstance()