#pragma once
#include "cScene.h"
class cEnemyAdmin;
class cBulletAdmin;
class cPlayer;
class cMap;
class cDoor;
class cCollAdmin;
class cTestScene : public cScene
{
private:
	cBulletAdmin * m_Bullet;
	cMap * m_TestMap;
	cEnemyAdmin * m_Enemy;
	cPlayer * m_Player;
	cDoor * m_Door[4];
	cCollAdmin * m_Coll;
	MapState m_MapState;
	bool IsDoorOpen;
public:
	cTestScene(MapState mapState);
	virtual ~cTestScene();

	void Reset();
	void Destory();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
};

