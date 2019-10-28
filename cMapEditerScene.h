#pragma once
#include "cScene.h"

class cMapEditerScene : public cScene
{
private:
	int State;
	Vec2 vCurTilePos;

	vector<cTile*> Tiles;
	vector<cTile*> ToSpawnTiles;

	void CheckCurrentTile();
	void SpawnTile();
public:
	cMapEditerScene();
	virtual ~cMapEditerScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

