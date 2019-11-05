#include "DXUT.h"
#include "cMapAdmin.h"

#include "cTestScene.h"

cMapAdmin::cMapAdmin()
{
	MaxCount = 7;
}


cMapAdmin::~cMapAdmin()
{
}

void cMapAdmin::Init()
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			Map[i][j].State = NONE;
			Map[i][j].vMyMatrix = Vec2(i, j);
			for (int k = 0; k < 4; k++) {
				Map[i][j].ConnectPath[k] = false;
			}
			CheckBoss[i][j] = false;
		}
	}

	
	Map[25][25].State = StartRoom;

	NowMap = Vec2(25, 25);
	MapCount = 0;

	IsGoldRoom = false;
	IsShopRoom = false;
	IsBossRoom = false;
}

void cMapAdmin::Update()
{
	if (INPUT->KeyDown('R')) {
		Init();
		Spawn();
	}

	if (INPUT->KeyPress(VK_SPACE)) {
		MaxCount++;
	}
}

void cMapAdmin::Spawn()
{
    while(MapCount < MaxCount) {
		SpawnMap(NowMap);
	    RandSelect();
    }

	if (!IsGoldRoom || !IsShopRoom || !IsBossRoom) {
	    Init();
	    Spawn();
	    DEBUG_LOG("Re");
	}
	else {
		SpawnScene();
		NowMap = Vec2(25, 25);
		ChangeScene(NowMap);
		DEBUG_LOG("End");
	}
}

void cMapAdmin::SpawnMap(Vec2 _NowMap)
{
	if (MapCount >= MaxCount)
		return;

	if (_NowMap.x > 1) {
		if (Map[(int)_NowMap.x - 1][(int)_NowMap.y].State == NONE) {
			if (rand() % 4 == 0) {
				MapCount++;
				Map[(int)_NowMap.x][(int)_NowMap.y].ConnectPath[LEFT] = true;
				//Map[(int)_NowMap.x - 1][(int)_NowMap.y].State = NormalRoom;
				SpawnRandMapState(Vec2(_NowMap.x - 1, _NowMap.y));
				Map[(int)_NowMap.x - 1][(int)_NowMap.y].ConnectPath[RIGHT] = true;
				//SpawnMap(Vec2(_NowMap.x - 1 , _NowMap.y));
			} 
		}
	}
	if (_NowMap.x < 50) {
		if (Map[(int)_NowMap.x + 1][(int)_NowMap.y].State == NONE) {
			if (rand() % 4 == 0) {
				MapCount++;
				Map[(int)_NowMap.x][(int)_NowMap.y].ConnectPath[RIGHT] = true;
				//Map[(int)_NowMap.x + 1][(int)_NowMap.y].State = NormalRoom;
				SpawnRandMapState(Vec2(_NowMap.x + 1, _NowMap.y));
				Map[(int)_NowMap.x + 1][(int)_NowMap.y].ConnectPath[LEFT] = true;
				//SpawnMap(Vec2(_NowMap.x + 1, _NowMap.y));
			}
		}
	}
	if (_NowMap.y > 1) {
		if (Map[(int)_NowMap.x][(int)_NowMap.y - 1].State == NONE) {
			if (rand() % 4 == 0) {
				MapCount++;
				Map[(int)_NowMap.x][(int)_NowMap.y].ConnectPath[BOTTOM] = true;
				//Map[(int)_NowMap.x][(int)_NowMap.y - 1].State = NormalRoom;
				SpawnRandMapState(Vec2(_NowMap.x, _NowMap.y - 1));
				Map[(int)_NowMap.x][(int)_NowMap.y - 1].ConnectPath[TOP] = true;
				//SpawnMap(Vec2(_NowMap.x, _NowMap.y - 1));
			}
		}
	}
	if (_NowMap.y < 50) {
		if (Map[(int)_NowMap.x][(int)_NowMap.y + 1].State == NONE) {
			if (rand() % 4 == 0) {
				MapCount++;
				Map[(int)_NowMap.x][(int)_NowMap.y].ConnectPath[TOP] = true;
				//Map[(int)_NowMap.x][(int)_NowMap.y + 1].State = NormalRoom;
				SpawnRandMapState(Vec2(_NowMap.x, _NowMap.y + 1));
				Map[(int)_NowMap.x][(int)_NowMap.y + 1].ConnectPath[BOTTOM] = true;
				//SpawnMap(Vec2(_NowMap.x, _NowMap.y + 1));
			}
		}
	}

	return;
}

void cMapAdmin::RandSelect()
{
	while (true)
	{
		int rand_x = rand() % 50;
		int rand_y = rand() % 50;
		if (Map[rand_x][rand_y].State != NONE && 
			Map[rand_x][rand_y].State != GoldRoom  && 
			Map[rand_x][rand_y].State != ShopRoom &&
			Map[rand_x][rand_y].State != BossRoom) {
			NowMap = Vec2(rand_x, rand_y);
			return;
		}
	}
}

void cMapAdmin::SpawnRandMapState(Vec2 _NowMap)
{
	if (MapCount > 1) {
		if (MaxCount - MapCount > 0) {
			if (rand() % (MaxCount - MapCount) == 0 && !IsGoldRoom) {
				IsGoldRoom = true;
				Map[(int)_NowMap.x][(int)_NowMap.y].State = GoldRoom;
				return;
			}
			if (rand() % (MaxCount - MapCount) == 0 && !IsShopRoom) {
				if (Map[(int)_NowMap.x - 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x + 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y + 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y - 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				IsShopRoom = true;
				Map[(int)_NowMap.x][(int)_NowMap.y].State = ShopRoom;
				return;
			}
			if (rand() % (MaxCount - MapCount) == 0 && !IsBossRoom) {
				if (Map[(int)_NowMap.x - 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x + 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y + 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y - 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				IsBossRoom = true;
				Map[(int)_NowMap.x][(int)_NowMap.y].State = BossRoom;
				return;
			}
		}
		else {
			if (!IsGoldRoom) {
				IsGoldRoom = true;
				Map[(int)_NowMap.x][(int)_NowMap.y].State = GoldRoom;
				return;
			}
			if (!IsShopRoom) {
				if (Map[(int)_NowMap.x - 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x + 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y + 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y - 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				IsShopRoom = true;
				Map[(int)_NowMap.x][(int)_NowMap.y].State = ShopRoom;
				return;
			}
			if (!IsBossRoom) {
				if (Map[(int)_NowMap.x - 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x + 1][(int)_NowMap.y].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y + 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				if (Map[(int)_NowMap.x][(int)_NowMap.y - 1].State == StartRoom) {
					Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
					return;
				}
				IsBossRoom = true;
				Map[(int)_NowMap.x][(int)_NowMap.y].State = BossRoom;
				return;
			}
		}
	}
	Map[(int)_NowMap.x][(int)_NowMap.y].State = NormalRoom;
	return;
}

void cMapAdmin::Render(Vec2 pos)
{

	//DEBUG_LOG(MaxCount);
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50;j++) {
			switch (Map[i][j].State)
			{
			case NONE:
				break;
			case StartRoom:
				IMAGE->Render(IMAGE->FindImage("StartRoom"), pos - Vec2(i * 60, j * 60), 0, true);
				break;
			case NormalRoom:
				IMAGE->Render(IMAGE->FindImage("NormalRoom"), pos - Vec2(i * 60, j * 60), 0, true);
				break;
			case GoldRoom:
				IMAGE->Render(IMAGE->FindImage("GoldRoom"), pos - Vec2(i * 60, j * 60), 0, true);
				break;
			case ShopRoom:
				IMAGE->Render(IMAGE->FindImage("ShopRoom"), pos - Vec2(i * 60, j * 60), 0, true);
				break;
			case BossRoom:
				IMAGE->Render(IMAGE->FindImage("BossRoom"), pos - Vec2(i * 60, j * 60), 0, true);
				break;
			default:
				break;
			}

			if (Map[i][j].ConnectPath[LEFT] == true) {
				IMAGE->Render(IMAGE->FindImage("Path"), pos - Vec2(i * 60 - 30, j * 60), 0, true);
			}
			if (Map[i][j].ConnectPath[RIGHT] == true) {
				IMAGE->Render(IMAGE->FindImage("Path"), pos - Vec2(i * 60 + 30, j * 60), 0, true);
			}
			if (Map[i][j].ConnectPath[TOP] == true) {
				IMAGE->Render(IMAGE->FindImage("Path"), pos - Vec2(i * 60, j * 60 + 30), 90, true);
			}
			if (Map[i][j].ConnectPath[BOTTOM] == true) {
				IMAGE->Render(IMAGE->FindImage("Path"), pos - Vec2(i * 60, j * 60 - 30), 90, true);
			}
		}
	}
	IMAGE->Render(IMAGE->FindImage("NowRoom"), pos - Vec2(NowMap.x * 60, NowMap.y * 60), 0, true);
	IMAGE->ReBegin(true);
	IMAGE->PrintText("ÃÖ´ë ¸Ê:" + to_string(MaxCount), Vec2(0, 0), 60, D3DCOLOR_XRGB(0, 0, 0));
	IMAGE->ReBegin(false);
}

void cMapAdmin::SpawnScene()
{
	//i_Count = 0;
	i_Count = 0;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (Map[i][j].State != MapState::NONE) {
				char str[128] = "Stage1_";
				sprintf(str, "%d", i_Count);
				DEBUG_LOG(i);
				SCENE->DeleteScene(str);
				Scenes[i][j] = SCENE->AddScene(str, new cTestScene((MapState)Map[i][j].State));
				i_Count++;
			}
		}
	}
}

void cMapAdmin::ChangeScene(Vec2 Map)
{
	NowMap = Map;
	SCENE->ChangeScene(Scenes[(int)(Map.x)][(int)(Map.y)]);
}