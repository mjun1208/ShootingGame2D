#pragma once
class cMap;
class cBullet;
class cPlayer
{
private:
	vector<cBullet *>& m_Bullet;
private:
	cTexture * m_Image;
	cTexture * m_MoveImage[4];
	cTexture * m_AttackImage[4];

	cFrame * m_MoveFrame_3;
	cFrame * m_MoveFrame_5;

	cFrame * m_AttackFrame;

	Vec2 m_vDir;
	Vec2 m_vPos;

	Dirction DirState;
	Dirction ShootDirState;

	bool b_Move;
	bool b_Attack;
	bool b_EndAttackFrame;

	void Movement();
	void CheckColl(cMap * map);
	void ShootBullet(Dirction Dir);
public:
	cPlayer(vector<cBullet *>& Bullet);
	~cPlayer();

	void Init();
	void Update(cMap * map);
	void Render();
	void Release();

	Vec2 GetPos() { return m_vPos; }
	void SetPos(Vec2 pos) { m_vPos = pos; }
};

