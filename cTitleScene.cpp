#include "DXUT.h"
#include "cTitleScene.h"

#include "cTestScene.h"
cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{

	m_BackGround = IMAGE->FindImage("TitleBackGround");
	m_StartButton = new cButton(Vec2(WINSIZEX / 2 - 400, WINSIZEY / 2 - 250), IMAGE->FindImage("StartButton"));
	m_OptionButton = new cButton(Vec2(WINSIZEX / 2 - 400, WINSIZEY / 2 - 100), IMAGE->FindImage("OptionButton"));
	m_CreditsButton = new cButton(Vec2(WINSIZEX / 2 - 400, WINSIZEY / 2 + 50), IMAGE->FindImage("CreditsButton"));
	m_ExitButton = new cButton(Vec2(WINSIZEX / 2 - 400, WINSIZEY / 2 + 200), IMAGE->FindImage("ExitButton"));
	m_MakeMap = new cButton(Vec2(WINSIZEX / 2, WINSIZEY / 2), IMAGE->FindImage("MakeMapButton"));
}

void cTitleScene::Update()
{
	if (INPUT->KeyDown('A'))
		SCENE->ChangeScene("Map");
	if (INPUT->KeyDown('S'))
		SCENE->ChangeScene("MiniMap");
	if (INPUT->KeyDown('D'))
		SCENE->ChangeScene("Test");



	if (m_CreditsButton->Update())
		DEBUG_LOG("农饭调");

	if (m_ExitButton->Update())
		PostQuitMessage(0);

	if (m_MakeMap->Update()) {
		SCENE->ChangeScene("Map");
	}

	if (m_OptionButton->Update())
		DEBUG_LOG("可记");

	if (m_StartButton->Update()) {
		//SCENE->AddScene("Test", new cTestScene);
		NowDoor = Dirction::FOLLOW;
		Stage1_MiniMap.Init();
		Stage1_MiniMap.Spawn();
		//SCENE->ChangeScene("Test");
	}


}

void cTitleScene::Render()
{
	IMAGE->CenterRender(m_BackGround, Vec2(0, 0), Vec3(0, 0, 0), 0);
	m_StartButton->Render();
	m_CreditsButton->Render();
	m_ExitButton->Render();

	m_OptionButton->Render();
	m_MakeMap->Render();
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_StartButton);
	SAFE_DELETE(m_CreditsButton);
	SAFE_DELETE(m_ExitButton);
	SAFE_DELETE(m_MakeMap);
	SAFE_DELETE(m_OptionButton);
}
