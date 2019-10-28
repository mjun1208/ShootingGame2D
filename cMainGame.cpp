#include "DXUT.h"
#include "cMainGame.h"

#include "cLoadScene.h"
#include "cTitleScene.h"
#include "cMapEditerScene.h"
#include "cMiniMapScene.h"
#include "cTestScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	srand(time(NULL));

	IMAGE->Init();
	CAMERA->Init();
	INPUT->Init();
	
	SCENE->AddScene("Load", new cLoadScene);
	SCENE->AddScene("Title", new cTitleScene);
	SCENE->AddScene("Map", new cMapEditerScene);
	SCENE->AddScene("MiniMap", new cMiniMapScene);
	SCENE->AddScene("Test", new cTestScene);

	SCENE->ChangeScene("Load");

}

void cMainGame::Update()
{
	CAMERA->Update();
	SCENE->Update();
	INPUT->Update();
}

void cMainGame::Render()
{
	CAMERA->SetTramsform();

	IMAGE->Begin(false);
	SCENE->Render();
	IMAGE->End();
	
}

void cMainGame::Release()
{
	cCameraManager::ResetInstance();
	cImageManager::ResetInstance();
	cInputManager::ResetInstance();
	cSceneManager::ResetInstance();
	cMapManager::ResetInstance();
}

void cMainGame::ResetDevice()
{
	IMAGE->LostDevice();
}

void cMainGame::LostDevice()
{
	IMAGE->ResetDevice();
}
