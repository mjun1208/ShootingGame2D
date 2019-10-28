#pragma once
class cMap;
class cBullet;
class cBulletAdmin
{
private:
	vector<cBullet *> m_Bullet;
public:
	cBulletAdmin();
	~cBulletAdmin();

	void Init();
	void Update(cMap * map);
	void Render();
	void Release();

	vector<cBullet *>& GetBullet() { return m_Bullet; }
};

