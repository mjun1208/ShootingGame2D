#include "DXUT.h"
#include "cMiniMapScene.h"

#include "cMapAdmin.h"

cMiniMapScene::cMiniMapScene()
{
}


cMiniMapScene::~cMiniMapScene()
{
}

void cMiniMapScene::Init()
{
	Map = new cMapAdmin;
	Map->Init();
	DEBUG_LOG("Mini");

	//CAMERA->SetPosition(Vec3(25 * 60, 25 * 60, 0));
}

void cMiniMapScene::Update()
{
	Map->Update();
	if (INPUT->KeyDown('M')) {
		Map->Spawn();
	}

	if (INPUT->KeyPress(VK_UP)) {
		CAMERA->SetPosition(Vec3(CAMERA->GetCameraPos().x, CAMERA->GetCameraPos().y - 10, 0));
	}
	if (INPUT->KeyPress(VK_DOWN)) {
		CAMERA->SetPosition(Vec3(CAMERA->GetCameraPos().x, CAMERA->GetCameraPos().y + 10, 0));
	}
	if (INPUT->KeyPress(VK_LEFT)) {
		CAMERA->SetPosition(Vec3(CAMERA->GetCameraPos().x - 10, CAMERA->GetCameraPos().y, 0));
	}
	if (INPUT->KeyPress(VK_RIGHT)) {
		CAMERA->SetPosition(Vec3(CAMERA->GetCameraPos().x + 10, CAMERA->GetCameraPos().y, 0));
	}
}

void cMiniMapScene::Render()
{
	Map->Render(Vec2(25 * 60 + WINSIZEX / 2, 25 * 60 + WINSIZEY / 2));
}

void cMiniMapScene::Release()
{
	SAFE_DELETE(Map);
}
