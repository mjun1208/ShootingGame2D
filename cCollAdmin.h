#pragma once
class cEnemyAdmin;
class cBulletAdmin;
class cCollAdmin
{
private:
	void Enemy_Bullet(cEnemyAdmin * Enemy , cBulletAdmin * Bullet);
public:
	cCollAdmin();
	~cCollAdmin();

	void Update(cEnemyAdmin * Enemy, cBulletAdmin * Bullet);
};

