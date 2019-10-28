#pragma once
#include "cScene.h"
class cMapAdmin;
class cMiniMapScene : public cScene
{
private:
	cMapAdmin * Map;
public:
	cMiniMapScene();
	virtual ~cMiniMapScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

