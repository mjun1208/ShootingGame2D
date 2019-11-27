#pragma once
#include "singleton.h"


class cMapManager : public singleton<cMapManager>
{
private:
	vector<cTile*> mapCode;
	vector<EnemyDumy*> enemyCode;
public:
	cMapManager();
	virtual ~cMapManager();

	void AddInfo(int _x, UINT _y, UINT _form);
	void AddEnemy(int _x, int _y, int _form);
	void Sort();
	void SaveInfo(int Stage);
	void LoadInfo(int Map);

	void Release();

	vector<cTile*>& OutInfo() { return mapCode; };
	vector<EnemyDumy*>& OutEnemyInfo() { return enemyCode; };
};

#define MapSet cMapManager::GetInstance()