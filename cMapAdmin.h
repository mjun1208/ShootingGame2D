#pragma once
enum MapState { NONE = -100, StartRoom = -75, GoldRoom = -50, ShopRoom = -25, BossRoom = -1 ,NormalRoom = 0 };
struct _Map
{
	int State;
	bool ConnectPath[4] = {false, };
	Vec2 vMyMatrix;
};
class cMapAdmin
{
private:
	cScene * Scenes[50][50];
	_Map Map[50][50];
	bool CheckBoss[50][50];
	Vec2 NowMap;
	int MapCount = 0;
	int MaxCount = 8;

	bool IsGoldRoom;
	bool IsShopRoom;
	bool IsBossRoom;

	int i_Count = 0;
public:
	cMapAdmin();
	~cMapAdmin();

	void Init();
	void Update();
	void Spawn();
	void SpawnMap(Vec2 _NowMap);
	void RandSelect();

	void SpawnRandMapState(Vec2 _NowMap);
	void Render(Vec2 pos);

	void ReSpawn() { Init(); Spawn();}

	void SpawnScene();
	void ChangeScene(Vec2 Map);
	_Map GetNowMap() { return Map[(int)NowMap.x][(int)NowMap.y]; }
};

