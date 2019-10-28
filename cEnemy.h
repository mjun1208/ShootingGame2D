#pragma once
class cMap;
class cEnemy
{
private:
	cTexture * m_Image;
	Vec2 m_vPos;
	Vec2 m_vDir;

	Vec2 m_vTarget;

	Vec2 m_vLastTargetPos;

	bool IsMove;

	vector<Vec2> Path;
	int NowPath;
	void Movement(Vec2 Target, cMap * map);
	void CheckColl(cMap * map);
public:
	cEnemy(cMap * map);
	~cEnemy();

	void Init(cMap * map);
	void Update(Vec2 Target, cMap * map);
	void Render();
	void Release();
};

