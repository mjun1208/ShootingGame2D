#include "DXUT.h"
#include "cMapManager.h"

cMapManager::cMapManager()
{
	ifstream mapIf;
	int i = 0;
	while (true) {
		char str[128] = "";
		sprintf(str, "./MapFile/Stage1/map(%d).txt", i);
		mapIf = ifstream(str);

		if (mapIf.is_open()) {

			i++;
			mapIf.close();
		}
		else {
			break;
		}
	}
	Stage1_MapCount = i - 1;
}

cMapManager::~cMapManager()
{
	Release();
}

void cMapManager::AddInfo(int _x, UINT _y, UINT _form)
{
	for (auto iter : mapCode)
	{
		if (iter->GetMatrix().x == _x && iter->GetMatrix().y == _y)
		{
			iter->SetState(_form);
			return;
		}
	}
	RECT rc = {0,0,0,0};
	mapCode.push_back(new cTile(rc, Vec2(_x, _y), (TileState)_form, Vec2(0,0)));
}

void cMapManager::AddEnemy(int _x, int _y, int _form)
{
	for (auto iter : enemyCode)
	{
		if (iter->vMatrix.x == _x && iter->vMatrix.y == _y)
		{
			iter->EnemyState = (EnemyKind)_form;
			return;
		}
	}
	enemyCode.push_back(new EnemyDumy(Vec2(0, 0), Vec2(_x,_y), (EnemyKind)_form));
}

void cMapManager::Sort()
{
}

void cMapManager::SaveInfo(int Stage)
{
	ofstream mapOf;
	ifstream mapIf;
	int i = 0;
	//string path;
	while (true) {
		char str[128] = "";
		switch (Stage)
		{
		case 1:
			sprintf(str, "./MapFile/Stage1/map(%d).txt", i);
			break;
		case 2:
			sprintf(str, "./MapFile/Stage2/map(%d).txt", i);
			break;
		case 3:
			sprintf(str, "./MapFile/Stage3/map(%d).txt", i);
			break;
		default:
			break;
		}
		mapIf = ifstream(str);

		if (mapIf.is_open()) {

			i++;
			mapIf.close();
		}
		else {
			mapOf = ofstream(str);
			break;
		}
	}
	string tempCode;
	for (auto iter : mapCode)
	{
		tempCode.append(" (");
		tempCode.append(to_string((int)iter->GetMatrix().x));
		tempCode.append(" ,");
		tempCode.append(to_string((int)iter->GetMatrix().y));
		tempCode.append(")\t");
		tempCode.append(to_string((int)iter->GetState()));
		tempCode.append("/\n");
		/*
		����ϰ� ���� �ؾ� ��
		*/
	}

	for (auto iter : enemyCode) {
		tempCode.append(" E_(");
		tempCode.append(to_string((int)iter->vMatrix.x));
		tempCode.append(" ,");
		tempCode.append(to_string((int)iter->vMatrix.y));
		tempCode.append(") ");
		tempCode.append(to_string((int)iter->EnemyState));
		tempCode.append("/\n");
	}
	if (mapOf.is_open())
	{
		mapOf << tempCode;
	}
	mapOf.close();
}

void cMapManager::LoadInfo(int Map)
{
	char str[128] = "";
	sprintf(str, "./MapFile/Stage1/map(%d).txt", Map);
	ifstream mapIf(str);

	if (!mapIf.is_open())
	{
		DEBUG_LOG("������ ����");
		return;
	}

	string tempCode;

	while (mapIf)
	{
		string tempStr;
		getline(mapIf, tempStr);
		tempCode.append(tempStr);
		if (tempStr.empty())
		{
			DEBUG_LOG("empty");
			continue;
		}
		string x;

		if (tempStr.at(1) != 'E')
		{
			for (int i = 0; i < 3; i++)
			{
				if (tempStr.at(2 + i) == ' ') break;
				else
				{
					x += tempStr.at(2 + i);
				}
			}

			string y;

			for (int i = 0; i < 3; i++)
			{
				if (tempStr.at(x.size() + 4 + i) == ')') break;
				else
				{
					y += tempStr.at(4 + i + x.size());
				}
			}

			string form;

			for (int i = 0; i < 3; i++)
			{
				if (tempStr.at(x.size() + y.size() + 6 + i) == '/') break;
				else
				{
					form += tempStr.at(x.size() + y.size() + 6 + i);
				}
			}
			AddInfo(stoi(x), stoi(y), stoi(form));
		}
		else {

			for (int i = 0; i < 3; i++)
			{
				if (tempStr.at(4 + i) == ' ') break;
				else
				{
					x += tempStr.at(4 + i);
				}
			}

			string y;

			for (int i = 0; i < 3; i++)
			{
				if (tempStr.at(x.size() + 6 + i) == ')') 
					break;
				else
				{
					y += tempStr.at(6 + i + x.size());
				}
			}

			string form;

			for (int i = 0; i < 3; i++)
			{
				if (tempStr.at(x.size() + y.size() + 8 + i) == '/') break;
				else
				{
					form += tempStr.at(x.size() + y.size() + 8 + i);
				}
			}
			AddEnemy(stoi(x), stoi(y), stoi(form));
		}
	}

	//DEBUG_LOG(tempCode);
	mapIf.close();
}

void cMapManager::Release()
{
	for (auto iter : mapCode) {
		SAFE_DELETE(iter);
	}
	mapCode.clear();

	for (auto iter : enemyCode)
		SAFE_DELETE(iter);
	enemyCode.clear();
}
