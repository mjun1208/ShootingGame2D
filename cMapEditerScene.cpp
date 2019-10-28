#include "DXUT.h"
#include "cMapEditerScene.h"

cMapEditerScene::cMapEditerScene()
{
}


cMapEditerScene::~cMapEditerScene()
{
	Release();
}

void cMapEditerScene::Init()
{
	DEBUG_LOG("Hello");
	State = 0;

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 8; j++) {
			RECT rc = {
				i * 100,
				j * 100,
				(i * 100) + 100,
				(j * 100) + 100
			};
			vCurTilePos = Vec2(i * 100 + 50, j * 100 + 50);
			Tiles.push_back(new cTile(rc, Vec2(i, j), Tile2, vCurTilePos));
		}
	}
}

void cMapEditerScene::Update()
{
	if (INPUT->KeyDown('1'))
		State = WoodBox;
	if (INPUT->KeyDown('2'))
		State = Pumpkin;
	if (INPUT->KeyDown('3'))
		State = Tile2;
	if (INPUT->KeyDown('4'))
		State = None;

	CheckCurrentTile();
	SpawnTile();
	//
	if (INPUT->KeyDown('L'))
	{
		MapSet->LoadInfo();
		MapSet->OutInfo();
	}
	if (INPUT->KeyDown('S')) {
		for (auto iter : Tiles)
			MapSet->AddInfo(iter->GetMatrix().x, iter->GetMatrix().y, iter->GetState());
		MapSet->SaveInfo();
	}
	//
	if (INPUT->KeyDown('W')) {
		for (auto iter : Tiles)
			DEBUG_LOG(iter->GetMatrix().x << " " << iter->GetMatrix().y << " " << iter->GetState());
	}
}

void cMapEditerScene::Render()
{
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 8; j++)
		IMAGE->Render(IMAGE->FindImage("Stage1_BackGroundTile"), Vec2(i * 100 + 50, j * 100 + 50), 0 , true);
	}
	for (int i = 0; i < 8; i++) {
		for (auto iter : Tiles) {
			if (iter->GetMatrix().y == i)
				iter->Render();
		}
	}

	cTexture * m_image;

	switch (State)
	{
	case WoodBox:
		m_image = IMAGE->FindImage("WoodBox");
		break;
	case Pumpkin:
		m_image = IMAGE->FindImage("Pumpkin")->FindImage(0);
		break;
	case Tile2:
		m_image = IMAGE->FindImage("Tile2");
		break;
	case None:
		m_image = IMAGE->FindImage("None");
	default:
		break;
	}
	IMAGE->CenterRender(m_image->FindImage(0), vCurTilePos, Vec3(m_image->info.Width / 2, m_image->info.Height - 50, 0), 0);
	//IMAGE->CenterRender(IMAGE->FindImage("Tile")->FindImage(State), vCurTilePos, 
	//	Vec3(IMAGE->FindImage("Tile")->FindImage(State)->info.Width / 2, IMAGE->FindImage("Tile")->FindImage(State)->info.Height - 50, 0),0);
}

void cMapEditerScene::Release()
{
	for (auto iter : Tiles) {
		SAFE_DELETE(iter);
	}
	Tiles.clear();

	for (auto iter : ToSpawnTiles) {
		SAFE_DELETE(iter);
	}
	ToSpawnTiles.clear();
}


void cMapEditerScene::CheckCurrentTile()
{
	for (auto iter = Tiles.begin(); iter != Tiles.end();) {
		POINT pt = { INPUT->GetMousePos().x , INPUT->GetMousePos().y };
		if (PtInRect(&(*iter)->Getrc(), pt)) {
			vCurTilePos = (*iter)->GetPos();//Vec2((*iter)->vMatrix.x * 100 + 50, (*iter)->vMatrix.y * 100 + 50);
			if (INPUT->MouseLPress()) {
				DEBUG_LOG((*iter)->GetMatrix().x << " " << (*iter)->GetMatrix().y);
				ToSpawnTiles.push_back(new cTile((*iter)->Getrc(), (*iter)->GetMatrix(), State, (*iter)->GetPos()));
				return;
			}
		}

		++iter;
	}
	return;
}

void cMapEditerScene::SpawnTile()
{
	for (auto iter = ToSpawnTiles.begin(); iter != ToSpawnTiles.end();) {
		for (auto _iter = Tiles.begin(); _iter != Tiles.end();) {
			if ((*iter)->GetMatrix() == (*_iter)->GetMatrix()) {
				SAFE_DELETE(*_iter);
				_iter = Tiles.erase(_iter);
			}
			else
				++_iter;
		}

		Tiles.push_back(new cTile((*iter)->Getrc(), (*iter)->GetMatrix(), State, (*iter)->GetPos()));
		SAFE_DELETE(*iter);
		iter = ToSpawnTiles.erase(iter);
	}
	return;
}