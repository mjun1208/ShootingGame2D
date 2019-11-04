#pragma once
class cDoor
{
private:
	cTexture * m_OpenImage;
	cTexture * m_CloseImage;
	RECT m_rc;
	Vec2 m_vPos;
	Dirction StateDir;
	float Angle;

	bool IsOpen;
public:
	cDoor(Dirction Dir);
	~cDoor();

	void Init();
	bool Update(bool open, Vec2 PlayerPos);
	void Render();

	Vec2 GetPos() { return m_vPos; }
};

