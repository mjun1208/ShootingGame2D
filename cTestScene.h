#pragma once
#include "cScene.h"
class cEnemyAdmin;
class cBulletAdmin;
class cPlayer;
class cMap;
class cTestScene : public cScene
{
private:
	cBulletAdmin * m_Bullet;
	cMap * m_TestMap;
	cEnemyAdmin * m_Enemy;
	cPlayer * m_Player;

public:
	cTestScene();
	virtual ~cTestScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
};

