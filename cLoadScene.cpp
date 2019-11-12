#include "DXUT.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
}


cLoadScene::~cLoadScene()
{
}

void cLoadScene::Init()
{
	m_NowLoad = 0;
	m_NowSoundLoad = 0;
	//Sound

	//Image
	Load("StartRoom", "./Image/MiniMap/StartRoom.png");
	Load("NormalRoom", "./Image/MiniMap/NormalRoom.png");
	Load("ShopRoom", "./Image/MiniMap/ShopRoom.png");
	Load("GoldRoom", "./Image/MiniMap/GoldRoom.png");
	Load("BossRoom", "./Image/MiniMap/BossRoom.png");
	Load("Path", "./Image/MiniMap/RoomPath.png");
	Load("NowRoom", "./Image/MiniMap/NowRoom.png");
	Load("Map", "./Image/MiniMap/Map.png");
	//Player
	Load("Player", "./Image/Player.png");

	Load("Player_Idle_Back", "./Image/Player/Idle/ghost_idle_back/(%d).png", 2);
	Load("Player_Idle_Front", "./Image/Player/Idle/ghost_idle_front/(%d).png", 2);
	Load("Player_Idle_Left", "./Image/Player/Idle/ghost_idle_left/(%d).png", 2);
	Load("Player_Idle_Right", "./Image/Player/Idle/ghost_idle_right/(%d).png", 2);

	Load("Player_Move_Back", "./Image/Player/Move/ghost_move_back/(%d).png", 3);
	Load("Player_Move_Front", "./Image/Player/Move/ghost_move_front/(%d).png", 3);
	Load("Player_Move_Left", "./Image/Player/Move/ghost_move_left/(%d).png", 5);
	Load("Player_Move_Right", "./Image/Player/Move/ghost_move_right/(%d).png", 5);

	Load("Player_Attack_Back", "./Image/Player/Attack/ghost_attack_back/(%d).png", 3);
	Load("Player_Attack_Front", "./Image/Player/Attack/ghost_attack_front/(%d).png", 3);
	Load("Player_Attack_Left", "./Image/Player/Attack/ghost_attack_left/(%d).png", 3);
	Load("Player_Attack_Right", "./Image/Player/Attack/ghost_attack_right/(%d).png", 3);

	Load("Player_Bullet", "./Image/Player/PlayerBullet.png");

	Load("Enemy", "./Image/Enemy.png");
	Load("Enemy_Path", "./Image/Enemy_Path.png");

	Load("Boss", "./Image/Boss.png");

	//Tiles
	Load("Stage1_BackGroundTile", "./Image/BackGroundTile/Stage1.png");
	Load("Stage2_BackGroundTile", "./Image/BackGroundTile/Stage2(%d).png", 1);
	Load("Stage3_BackGroundTile", "./Image/BackGroundTile/Stage3(%d).png", 2);

	Load("WoodBox", "./Image/Tile/WoodBox/(0).png");
	Load("WoodBox_Hat", "./Image/Tile/WoodBox/Hat.png");

	Load("Pumpkin", "./Image/Tile/Pumpkin/Normal/(%d).png", 5);
	Load("Pumpkin_Hat", "./Image/Tile/Pumpkin/Normal/Hat/(0).png");
	Load("Pumpkin_Break", "./Image/Tile/Pumpkin/Break/(%d).png", 5);
	Load("Pumpkin_BreakHat", "./Image/Tile/Pumpkin/Break/Hat/(%d).png", 5);

	Load("Stage1_0", "./Image/Tile/Stage1/0/(0).png");
	Load("Stage1_0_Hat", "./Image/Tile/Stage1/0/Hat.png");
	Load("Stage1_1", "./Image/Tile/Stage1/1/(0).png");
	Load("Stage1_1_Hat", "./Image/Tile/Stage1/1/Hat.png");


	Load("Tile2", "./Image/Tile/Tile(2).png");

	Load("None", "./Image/Tile/None.png");

	Load("StartRoomDummy", "./Image/Dummy/Start.png");
	Load("ShopRoomDummy", "./Image/Dummy/Shop.png");
	Load("GoldRoomDummy", "./Image/Dummy/Gold.png");
	Load("BossRoomDummy", "./Image/Dummy/Boss.png");

	//Door
	Load("Close_Door", "./Image/Door/Close.png");
	Load("Open_Door", "./Image/Door/Open.png");

	//Wall
	Load("Wall_1", "./Image/Wall/Wall_1.png");
	Load("Wall_2", "./Image/Wall/Wall_2.png");
	Load("Wall_3", "./Image/Wall/Wall_3(%d).png",5);

	Load("Wall_Corner", "./Image/Wall/Wall_Corner.png");

	//Button
	Load("TestButton", "./Image/TestButton.png");

	//Title
	Load("TitleBackGround", "./Image/Title/BackGround/TitleBackGround.png");
	Load("CreditsButton", "./Image/Title/Button/CreditsButton.png");
	Load("ExitButton", "./Image/Title/Button/ExitButton.png");
	Load("OptionButton", "./Image/Title/Button/OptionButton.png");
	Load("StartButton", "./Image/Title/Button/StartButton.png");
	Load("MakeMapButton", "./Image/Title/Button/MakeMapButton.png");

	//MakeMap
	Load("MakeMap_Interface", "./Image/MakeMap/Interface.png");
	Load("MakeMap_Stage1_Button", "./Image/MakeMap/Stage1.png");
	Load("MakeMap_Stage2_Button", "./Image/MakeMap/Stage2.png");
	Load("MakeMap_Stage3_Button", "./Image/MakeMap/Stage3.png");
	Load("MakeMap_Save_Button", "./Image/MakeMap/Save.png");
	Load("MakeMap_Title_Button", "./Image/MakeMap/Title.png");
	
	Load("MakeMap_MiniMap", "./Image/MakeMap/MiniMap/MiniMap.png");
	Load("MakeMap_MiniMap_Tile", "./Image/MakeMap/MiniMap/Tile(%d).png",1);
	Load("MakeMap_MiniMap_Pumpkin", "./Image/MakeMap/MiniMap/Pumpkin.png");
	Load("MakeMap_MiniMap_Enemy", "./Image/MakeMap/MiniMap/Enemy.png");


	m_MaxSoundLoad = m_SoundLoad.size();
	m_MaxLoad = m_Load.size();
}

void cLoadScene::Update()
{
	if (m_NowLoad != m_MaxLoad) {
		IMAGE->AddImage(
			m_Load[m_NowLoad].key,
			m_Load[m_NowLoad].path,
			m_Load[m_NowLoad].count
		);

		m_NowLoad++;
	}
	else if (m_NowSoundLoad != m_MaxSoundLoad) {
		INPUT->AddSound(
			m_SoundLoad[m_NowSoundLoad].key,
			m_SoundLoad[m_NowSoundLoad].path
		);

		m_NowSoundLoad++;
	}
	else {
		//이미지 추가가 다 되었으면 Scene을 변경한다.
		SCENE->ChangeScene("Title");
	}
}

void cLoadScene::Render()
{
}

void cLoadScene::Release()
{
}
