#pragma once
#include "cScene.h"
#include "cEnemy.h"

class cMapEditerScene : public cScene
{
private:
	bool EnemyMode;

	int BackGroundArray[15][15];

	int i_NowStage;

	bool IsInit;

	Vec2 vCameraPos;
	
	bool IsInterface;

	cTexture * m_BackGround;
	TileState m_FirstTile;

	cTexture * m_InterFace;
	Vec2 vInterFacePos;

	cButton * SaveButton;
	cButton * Stage1Button;
	cButton * Stage2Button;
	cButton * Stage3Button;
	cButton * TitleButton;

	bool IsSave;
	float SaveColorAlpha;

	TileState State;
	EnemyKind EnemyState;
	Vec2 vCurTilePos;

	vector<cTile*> Tiles;
	vector<cTile*> ToSpawnTiles;

	vector<EnemyDumy*> Enemys;
	vector<EnemyDumy*> ToSpawnEnemys;

	void CheckCurrentTile();
	void SpawnTile();
	
	void SpawnEnemy();
public:
	cMapEditerScene(int Stage);
	virtual ~cMapEditerScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

