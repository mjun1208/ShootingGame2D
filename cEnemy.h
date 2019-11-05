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
	bool b_Del;

	RECT m_rc;

	vector<Vec2> Path;
	int NowPath;
	void Movement(Vec2 Target, cMap * map);
	void CheckColl(cMap * map);

	int i_Hp;
public:
	cEnemy(cMap * map);
	~cEnemy();

	void Init(cMap * map);
	void Update(Vec2 Target, cMap * map);
	void Render();
	void Release();

	RECT Getrc() { return m_rc; }

	int GetHp() { return i_Hp; };
	void SetHp(int Hp) { i_Hp = Hp; }

	Vec2 GetPos() { return m_vPos; }
	void SetPos(Vec2 vPos) { m_vPos = vPos; }

	bool GetDel() { return b_Del; }
	void SetDel(bool del) { b_Del = del; }
};

