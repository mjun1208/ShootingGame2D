#include "DXUT.h"
#include "cTestScene.h"

#include "cBulletAdmin.h"
#include "cEnemyAdmin.h"
#include "cCollAdmin.h"
#include "cPlayer.h"

#include "cMap.h"
#include "cDoor.h"
#include "cEnemy.h"
cTestScene::cTestScene(MapState mapState)
	: m_MapState(mapState)
{
	Reset();
}


cTestScene::~cTestScene()
{
	Destory();
}

void cTestScene::Reset()
{
	if (m_MapState == Normal) {
		Now_Stage1_Map = rand() % (Stage1_MapCount + 1);
		DEBUG_LOG(Now_Stage1_Map);
	}
	else
		Now_Stage1_Map = -1;
	m_TestMap = new cMap(1, Now_Stage1_Map);
	m_TestMap->Init();

	m_Enemy = new cEnemyAdmin();
	m_Enemy->Init();
	if (m_MapState == NormalRoom)
		m_Enemy->GetEnemy().push_back(new cEnemy(m_TestMap));

	m_Bullet = new cBulletAdmin();
	m_Bullet->Init(); 

	m_Player = new cPlayer(m_Bullet->GetBullet());
	m_Player->Init();
	
	for (int i = 0; i < 4; i++) {
		m_Door[i] = new cDoor(Dirction(i));
	}

	m_Coll = new cCollAdmin();
}

void cTestScene::Destory()
{
	SAFE_DELETE(m_TestMap);
	SAFE_DELETE(m_Enemy);
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Bullet);
	SAFE_DELETE(m_Coll);

	for (int i = 0; i < 4; i++) {
		SAFE_DELETE(m_Door[i]);
	}
}

void cTestScene::Init()
{
	Vec2 PlayerPos;
	switch (NowDoor)
	{
	case LEFT:
		PlayerPos = m_Door[LEFT]->GetPos() + Vec2(-50, 0);
		break;
	case RIGHT:
		PlayerPos = m_Door[RIGHT]->GetPos() + Vec2(50, 0);
		break;
	case TOP:
		PlayerPos = m_Door[TOP]->GetPos() + Vec2(0, 50);
		break;
	case BOTTOM:
		PlayerPos = m_Door[BOTTOM]->GetPos() + Vec2(0,-50);
		break;
	case FOLLOW:
		PlayerPos = Vec2(150, 100);
		break;
	default:
		break;
	}
	m_Player->SetPos(PlayerPos);
	IsDoorOpen = false;
}

void cTestScene::Update()
{
	if (m_Enemy->GetEnemy().size() <= 0) {
		IsDoorOpen = true;
	}

	m_TestMap->Update();
	m_Player->Update(m_TestMap);
	m_Enemy->Update(m_Player->GetPos(), m_TestMap);
	m_Bullet->Update(m_TestMap);
	m_Coll->Update(m_Enemy, m_Bullet);
	for (int i = 0; i < 4; i++) {
		if (Stage1_MiniMap.GetNowMap().ConnectPath[i]) {
			if (m_Door[i]->Update(IsDoorOpen, m_Player->GetPos())) {
				switch (i)
				{
				case LEFT:
					NowDoor = RIGHT;
					Stage1_MiniMap.ChangeScene(Vec2(Stage1_MiniMap.GetNowMap().vMyMatrix.x - 1, Stage1_MiniMap.GetNowMap().vMyMatrix.y));
					break;
				case RIGHT:
					NowDoor = LEFT;
					Stage1_MiniMap.ChangeScene(Vec2(Stage1_MiniMap.GetNowMap().vMyMatrix.x + 1, Stage1_MiniMap.GetNowMap().vMyMatrix.y));
					break;
				case TOP:
					NowDoor = BOTTOM;
					Stage1_MiniMap.ChangeScene(Vec2(Stage1_MiniMap.GetNowMap().vMyMatrix.x, Stage1_MiniMap.GetNowMap().vMyMatrix.y + 1));
					break;
				case BOTTOM:
					NowDoor = TOP;
					Stage1_MiniMap.ChangeScene(Vec2(Stage1_MiniMap.GetNowMap().vMyMatrix.x, Stage1_MiniMap.GetNowMap().vMyMatrix.y - 1));
					break;
				default:
					break;
				}
			}
		}
	}
	if (INPUT->KeyDown('R'))
		SCENE->ChangeScene("Test");

	if (INPUT->KeyDown('1')) {
		if (Now_Stage1_Map > 0) {
			Now_Stage1_Map--;
		}
		SCENE->ChangeScene("Test");
	}

	if (INPUT->KeyDown('2')) {
		if (Now_Stage1_Map < Stage1_MapCount) {
			Now_Stage1_Map++;
		}
		SCENE->ChangeScene("Test");
	}
}

void cTestScene::Render()
{
	m_TestMap->BackGroundRender();
	m_TestMap->Render();
	switch (m_MapState)
	{
	case NONE:
		break;
	case StartRoom:
		IMAGE->Render(IMAGE->FindImage("StartRoomDummy"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0, true);
		break;
	case GoldRoom:
		IMAGE->Render(IMAGE->FindImage("GoldRoomDummy"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0, true);
		break;
	case ShopRoom:
		IMAGE->Render(IMAGE->FindImage("ShopRoomDummy"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0, true);
		break;
	case BossRoom:
		IMAGE->Render(IMAGE->FindImage("BossRoomDummy"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0, true);
		break;
	case NormalRoom:
		break;
	default:
		break;
	}

	m_Enemy->Render();
	m_Player->Render();
	m_Bullet->Render();
	m_TestMap->HatRender();
	for (int i = 0; i < 4; i++) {
		if (Stage1_MiniMap.GetNowMap().ConnectPath[i]) 
			m_Door[i]->Render();
	}

	if (INPUT->KeyPress('Q')) {
		for (auto iter : m_TestMap->GetTile()) {
			if (iter->GetState() == 0)
				Rectangle(GetDC(DXUTGetHWND()), iter->Getrc().left, iter->Getrc().top, iter->Getrc().right, iter->Getrc().bottom);
		}
	}
	if (INPUT->KeyPress('M')) {
		IMAGE->ReBegin(true);
		IMAGE->Render(IMAGE->FindImage("Map"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0, true);
		Stage1_MiniMap.Render(Vec2(25 * 60 + WINSIZEX / 2, 25 * 60 + WINSIZEY / 2));
		IMAGE->ReBegin(false);
	}
}

void cTestScene::Release()
{
}
