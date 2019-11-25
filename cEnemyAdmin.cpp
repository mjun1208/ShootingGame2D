#include "DXUT.h"
#include "cEnemyAdmin.h"

#include "cEnemy.h"

#include "cMap.h"

cEnemyAdmin::cEnemyAdmin()
{
}


cEnemyAdmin::~cEnemyAdmin()
{
	Release();
}

void cEnemyAdmin::Init()
{
}

void cEnemyAdmin::Update(Vec2 Target, cMap * map)
{
	//if (b_Once) {
	//	b_Once = false;
	//	m_Enemy.push_back(new cEnemy(map));
	//}

	for (auto iter : m_Enemy)
		iter->Update(Target, map);

	for (auto iter = m_Enemy.begin(); iter != m_Enemy.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_Enemy.erase(iter);
		}
		else
			++iter;
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_Enemy)
		iter->Render();
}

void cEnemyAdmin::Release()
{
	for (auto iter : m_Enemy)
		SAFE_DELETE(iter);

	m_Enemy.clear();
}
