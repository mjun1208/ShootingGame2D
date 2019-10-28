#include "DXUT.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	m_TestButton = new cButton(Vec2(WINSIZEX / 2, WINSIZEY / 2), IMAGE->FindImage("TestButton"));
}

void cTitleScene::Update()
{
	if (INPUT->KeyDown('A'))
		SCENE->ChangeScene("Map");
	if (INPUT->KeyDown('S'))
		SCENE->ChangeScene("MiniMap");
	if (INPUT->KeyDown('D'))
		SCENE->ChangeScene("Test");

	if (m_TestButton->Update()) {
		DEBUG_LOG("Test");
	}
}

void cTitleScene::Render()
{
	m_TestButton->Render();
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_TestButton);
}
