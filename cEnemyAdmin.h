#pragma once
class cMap;
class cEnemy;
class cEnemyAdmin
{
private:
	bool b_Once = true;
	vector<cEnemy*> m_Enemy;
public:
	cEnemyAdmin();
	~cEnemyAdmin();

	void Init();
	void Update(Vec2 Target , cMap * map);
	void Render();
	void Release();

	vector<cEnemy*>& GetEnemy() { return m_Enemy; };
};

