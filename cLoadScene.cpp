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

	//Player
	Load("Player", "./Image/Player.png");
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

	Load("WoodBox", "./Image/Tile/WoodBox/(0).png");
	Load("WoodBox_Hat", "./Image/Tile/WoodBox/Hat.png");

	Load("Pumpkin", "./Image/Tile/Pumpkin/Normal/(%d).png", 5);
	Load("Pumpkin_Hat", "./Image/Tile/Pumpkin/Normal/Hat/(0).png");
	Load("Pumpkin_Break", "./Image/Tile/Pumpkin/Break/(%d).png", 5);
	Load("Pumpkin_BreakHat", "./Image/Tile/Pumpkin/Break/Hat/(%d).png", 5);


	Load("Tile2", "./Image/Tile/Tile(2).png");

	Load("None", "./Image/Tile/None.png");

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
