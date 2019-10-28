#include "DXUT.h"
#include "cTestScene.h"

#include "cBulletAdmin.h"
#include "cEnemyAdmin.h"
#include "cPlayer.h"

#include "cMap.h"
cTestScene::cTestScene()
{
}


cTestScene::~cTestScene()
{
}

void cTestScene::Init()
{
	m_TestMap = new cMap();
	m_TestMap->Init();

	m_Enemy = new cEnemyAdmin();
	m_Enemy->Init();

	m_Bullet = new cBulletAdmin();
	m_Bullet->Init();

	m_Player = new cPlayer(m_Bullet->GetBullet());
	m_Player->Init();
}

void cTestScene::Update()
{
	m_TestMap->Update();
	m_Player->Update(m_TestMap);
	m_Enemy->Update(m_Player->GetPos(), m_TestMap);
	m_Bullet->Update(m_TestMap);

	if (INPUT->KeyDown('R'))
		SCENE->ChangeScene("Test");
}

void cTestScene::Render()
{
	m_TestMap->BackGroundRender();
	m_TestMap->Render();
	m_Enemy->Render();
	m_Player->Render();
	m_Bullet->Render();
	m_TestMap->HatRender();

	if (INPUT->KeyPress('Q')) {
		for (auto iter : m_TestMap->GetTile()) {
			if (iter->GetState() == 0)
				Rectangle(GetDC(DXUTGetHWND()), iter->Getrc().left, iter->Getrc().top, iter->Getrc().right, iter->Getrc().bottom);
		}
	}
}

void cTestScene::Release()
{
	SAFE_DELETE(m_TestMap);
	SAFE_DELETE(m_Enemy);
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Bullet);
}
