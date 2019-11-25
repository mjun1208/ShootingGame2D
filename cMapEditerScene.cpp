#include "DXUT.h"
#include "cMapEditerScene.h"

cMapEditerScene::cMapEditerScene(int Stage)
	:i_NowStage(Stage)
{
	IsInit = false;
}


cMapEditerScene::~cMapEditerScene()
{
	Release();
}

void cMapEditerScene::Init()
{
	EnemyMode = false;
	IsInit = true;
	switch (i_NowStage)
	{
	case 1:	
		m_BackGround = IMAGE->FindImage("Stage1_BackGroundTile");
		m_FirstTile = Stage1_0;
		break;
	case 2:	
		m_BackGround = IMAGE->FindImage("Stage2_BackGroundTile");
		m_FirstTile = Stage1_0;
		break;
	case 3:	
		m_BackGround = IMAGE->FindImage("Stage3_BackGroundTile");
		m_FirstTile = Stage1_0;
		break;
	default:
		break;
	}

	m_InterFace = IMAGE->FindImage("MakeMap_Interface");

	State = (TileState)0;
	EnemyState = TEST;

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			RECT rc = {
				i * 100,
				j * 100,
				(i * 100) + 100,
				(j * 100) + 100
			};
			vCurTilePos = Vec2(i * 100 + 50, j * 100 + 50);
			if (i == 0 || j == 0 || i == 14 || j == 14)
				Tiles.push_back(new cTile(rc, Vec2(i, j), m_FirstTile, vCurTilePos));
			else
				Tiles.push_back(new cTile(rc, Vec2(i, j), None, vCurTilePos));
			switch (i_NowStage)
			{
			case 1:
				BackGroundArray[i][j] = 0;
				break;
			case 2:
				int Stage2BackNowTile;
				if ((i + j + 1) % 2 == 1) 
					Stage2BackNowTile = 0;
				else 
					Stage2BackNowTile = 1;
				BackGroundArray[i][j] = Stage2BackNowTile;
				break;
			case 3:
				BackGroundArray[i][j] = rand() % 3;
				break;
			default:
				break;
			}
		}
	}

	vCameraPos = Vec2(WINSIZEX / 2, WINSIZEY / 2);
	vInterFacePos = Vec2(WINSIZEX / 2 + 150, WINSIZEY / 2);
	IsInterface = false;

	SaveButton = new cButton(Vec2(WINSIZEX - 75, 600), IMAGE->FindImage("MakeMap_Save_Button"));
	TitleButton = new cButton(Vec2(WINSIZEX - 225, 600), IMAGE->FindImage("MakeMap_Title_Button"));
	Stage1Button = new cButton(Vec2(WINSIZEX - 250, 350), IMAGE->FindImage("MakeMap_Stage1_Button"));
	Stage2Button = new cButton(Vec2(WINSIZEX - 150, 350), IMAGE->FindImage("MakeMap_Stage2_Button"));
	Stage3Button = new cButton(Vec2(WINSIZEX - 50, 350), IMAGE->FindImage("MakeMap_Stage3_Button"));

	SaveColorAlpha = 255;
	IsSave = false;
}

void cMapEditerScene::Update()
{
	if (INPUT->KeyDown('M')) {
		if (EnemyMode)
			EnemyMode = false;
		else
			EnemyMode = true;
	}

	if (!EnemyMode) {
		if (INPUT->KeyDown('1'))
			State = WoodBox;
		if (INPUT->KeyDown('2'))
			State = Pumpkin;
		if (INPUT->KeyDown('3'))
			State = Stage1_0;
		if (INPUT->KeyDown('4'))
			State = Stage1_1;
		if (INPUT->KeyDown('5'))
			State = None;
	}
	else {
		EnemyState = TEST;
	}

	if (INPUT->KeyPress('W') && vCameraPos.y > WINSIZEY / 2 - 40)
		vCameraPos.y -= 20;
	if (INPUT->KeyPress('S') && vCameraPos.y < 1500 - WINSIZEY / 2 - 40)
		vCameraPos.y += 20;
	if (INPUT->KeyPress('A') && vCameraPos.x > WINSIZEX / 2)
		vCameraPos.x -= 20;
	if (INPUT->KeyPress('D') && vCameraPos.x < 1500 - WINSIZEX / 2)
		vCameraPos.x += 20;

	CAMERA->SetPosition(Vec3(vCameraPos.x, vCameraPos.y, 0));

	if (INPUT->KeyDown('Q')) {
		if (!IsInterface)
			IsInterface = true;
		else
			IsInterface = false;
	}

	if (IsInterface) {
		D3DXVec2Lerp(&vInterFacePos, &vInterFacePos, &Vec2(WINSIZEX - 150, WINSIZEY / 2), 0.6f);
		if (SaveButton->Update()) {
			for (auto iter : Tiles)
				MapSet->AddInfo(iter->GetMatrix().x, iter->GetMatrix().y, iter->GetState());
			MapSet->SaveInfo(i_NowStage);

			IsSave = true;
			SaveColorAlpha = 255;
		}
		if (Stage1Button->Update()) {
			SCENE->ChangeScene("Map");
		}
		if (Stage2Button->Update()) {
			SCENE->ChangeScene("Map2");
		}
		if (Stage3Button->Update()) {
			SCENE->ChangeScene("Map3");
		}
		if (TitleButton->Update()) {
			CAMERA->SetPosition(Vec3(WINSIZEX / 2, WINSIZEY / 2, 0));
			SCENE->ChangeScene("Title");
		}
	}
	else {
		D3DXVec2Lerp(&vInterFacePos, &vInterFacePos, &Vec2(WINSIZEX + 150, WINSIZEY / 2), 0.6f);

		if (!EnemyMode) {
			CheckCurrentTile();
			SpawnTile();
		}
		else {
			CheckCurrentTile();
			SpawnEnemy();
		}
	}
	//if (INPUT->KeyDown('S')) {
	//	for (auto iter : Tiles)
	//		MapSet->AddInfo(iter->GetMatrix().x, iter->GetMatrix().y, iter->GetState());
	//	MapSet->SaveInfo();
	//}

	if (IsSave) {
		SaveColorAlpha = Lerp(SaveColorAlpha, 0.f, 0.06f);
		if (SaveColorAlpha <= 0) {
			IsSave = false;
			SaveColorAlpha = 255;
		}
	}
}

void cMapEditerScene::Render()
{
	if (i_NowStage == 2) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				IMAGE->Render(m_BackGround->FindImage(BackGroundArray[i][j]), Vec2(i * 200 + 100, j * 200 + 100), 0, true);
			}
		}
	}
	else {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				IMAGE->Render(m_BackGround->FindImage(BackGroundArray[i][j]), Vec2(i * 100 + 50, j * 100 + 50), 0, true);
			}
		}
	}

	for (int i = 0; i < 15; i++) {
		for (auto iter : Tiles) {
			if (iter->GetMatrix().y == i)
				iter->Render();
		}
	}

	for (auto iter : Enemys) {
		iter->m_Image = IMAGE->FindImage("Enemy");
		IMAGE->Render(IMAGE->FindImage("Enemy"), iter->vPos, 0, true);
	}

	cTexture * m_image;

	if (!EnemyMode) {
		switch (State)
		{
		case WoodBox:
			m_image = IMAGE->FindImage("WoodBox");
			break;
		case Pumpkin:
			m_image = IMAGE->FindImage("Pumpkin")->FindImage(0);
			break;
		case Stage1_0:
			m_image = IMAGE->FindImage("Stage1_0");
			break;
		case Stage1_1:
			m_image = IMAGE->FindImage("Stage1_1");
			break;
		case None:
			m_image = IMAGE->FindImage("None");
			break;
		default:
			break;
		}
	}
	else {
		switch (EnemyState)
		{
		case TEST:
			m_image = IMAGE->FindImage("Enemy");
			break;
		default:
			break;
		}
	}

	if (IsInterface) {
		IMAGE->ReBegin(true);
		IMAGE->Render(m_InterFace, vInterFacePos, 0, true);

		IMAGE->Render(IMAGE->FindImage("MakeMap_MiniMap"), Vec2(WINSIZEX - 150, 150), 0, true);

	    for (auto iter : Tiles) {
	    	switch (iter->GetState())
	    	{
	    	case None:
	    		break;
	    	case Stage1_0:
	    		IMAGE->Render(IMAGE->FindImage("MakeMap_MiniMap_Tile")->FindImage(0), Vec2(WINSIZEX - 300 + (iter->GetMatrix().x * 20 + 10) , (iter->GetMatrix().y * 20 + 10)), 0, true);
	    		break;
	    	case Stage1_1:
	    		IMAGE->Render(IMAGE->FindImage("MakeMap_MiniMap_Tile")->FindImage(1), Vec2(WINSIZEX - 300 + (iter->GetMatrix().x * 20 + 10), (iter->GetMatrix().y * 20 + 10)), 0, true);
	    		break;
	    	case Pumpkin:
	    		IMAGE->Render(IMAGE->FindImage("MakeMap_MiniMap_Pumpkin"), Vec2(WINSIZEX - 300 + (iter->GetMatrix().x * 20 + 10), (iter->GetMatrix().y * 20 + 10)), 0, true);
	    		break;
	    	default:
	    		break;
	    	}
	    }

		for (auto iter : Enemys) {
			switch (iter->EnemyState)
			{
			case TEST:
				IMAGE->Render(IMAGE->FindImage("MakeMap_MiniMap_Enemy")->FindImage(0), Vec2(WINSIZEX - 300 + (iter->vMatrix.x * 20 + 10), (iter->vMatrix.y * 20 + 10)), 0, true);
			default:
				break;
			}
		}

		Stage1Button->Render();
		Stage2Button->Render();
		Stage3Button->Render();
		SaveButton->Render();
		TitleButton->Render();
		IMAGE->ReBegin(false);
	}
	else {
		if (!EnemyMode)
			IMAGE->CenterRender(m_image->FindImage(0), vCurTilePos, Vec3(m_image->info.Width / 2, m_image->info.Height - 50, 0), 0);
		else
			IMAGE->CenterRender(m_image->FindImage(0), vCurTilePos, Vec3(m_image->info.Width / 2, m_image->info.Height / 2, 0), 0);
	}


	if (IsSave) {
		IMAGE->ReBegin(true);
		//D3DXColorLerp
		IMAGE->PrintText("저장 완료", Vec2(WINSIZEX / 2, WINSIZEY / 2), 100, D3DCOLOR_ARGB((DWORD)SaveColorAlpha, 255, 0, 0), true);
		IMAGE->ReBegin(false);
	}
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

	for (auto iter : Enemys) {
		SAFE_DELETE(iter);
	}
	Enemys.clear();

	for (auto iter : ToSpawnEnemys) {
		SAFE_DELETE(iter);
	}
	ToSpawnEnemys.clear();

	if (IsInit) {
		SAFE_DELETE(SaveButton);
		SAFE_DELETE(TitleButton);
		SAFE_DELETE(Stage1Button);
		SAFE_DELETE(Stage2Button);
		SAFE_DELETE(Stage3Button);
	}
}


void cMapEditerScene::CheckCurrentTile()
{
	for (auto iter = Tiles.begin(); iter != Tiles.end();) {
		POINT pt = { INPUT->GetScrollPos().x , INPUT->GetScrollPos().y };
		if (PtInRect(&(*iter)->Getrc(), pt)) {
			vCurTilePos = (*iter)->GetPos(); //Vec2((*iter)->vMatrix.x * 100 + 50, (*iter)->vMatrix.y * 100 + 50);
			if (INPUT->MouseLPress()) {
				DEBUG_LOG((*iter)->GetMatrix().x << " " << (*iter)->GetMatrix().y);
				if (!EnemyMode)
					ToSpawnTiles.push_back(new cTile((*iter)->Getrc(), (*iter)->GetMatrix(), State, (*iter)->GetPos()));
				else
					ToSpawnEnemys.push_back(new EnemyDumy((*iter)->GetPos(),(*iter)->GetMatrix(), EnemyState));
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

void cMapEditerScene::SpawnEnemy()
{
	for (auto iter = ToSpawnEnemys.begin(); iter != ToSpawnEnemys.end();) {
		for (auto _iter = Enemys.begin(); _iter != Enemys.end();) {
			if ((*iter)->vPos == (*_iter)->vPos) {
				SAFE_DELETE(*_iter);
				_iter = Enemys.erase(_iter);
			}
			else
				++_iter;
		}

		Enemys.push_back(new EnemyDumy((*iter)->vPos, (*iter)->vMatrix ,  (*iter)->EnemyState));
		SAFE_DELETE(*iter);
		iter = ToSpawnEnemys.erase(iter);
	}
	return;
}
