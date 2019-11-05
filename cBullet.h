#pragma once
class cMap;
enum BulletTag{
	PlayerBullet
};
class cBullet abstract
{
protected:
	int DirState;
	BulletTag m_Tag;
	cTexture * m_image;
	Vec2 m_vDir;
	Vec2 m_vPos;

	float f_LifeTime = 0;
	float f_CheckTime = 0;

	bool b_Del = false;

	RECT m_rc;
public:
	cBullet(Vec2 Pos, int Dir);
	virtual ~cBullet();

	virtual void Update() PURE;
	virtual void Render() PURE;

	void CheckColl(cMap * map);

	bool GetDel() { return b_Del; }
	void SetDel(bool del) { b_Del = del; }
	BulletTag GetTag() { return m_Tag; }
	RECT Getrc() { return m_rc; }
};

