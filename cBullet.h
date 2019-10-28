#pragma once
class cMap;
class cBullet abstract
{
protected:
	int DirState;

	cTexture * m_image;
	Vec2 m_vDir;
	Vec2 m_vPos;

	float f_LifeTime = 0;
	float f_CheckTime = 0;

	bool b_Del = false;
public:
	cBullet(Vec2 Pos, int Dir);
	virtual ~cBullet();

	virtual void Update() PURE;
	virtual void Render() PURE;

	void CheckColl(cMap * map);

	bool GetDel() { return b_Del; }
};

