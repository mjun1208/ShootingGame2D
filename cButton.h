#pragma once
enum ButtonState
{ Normal, OnCursor, Click};
class cButton
{
private:
	RECT m_rc;
	cTexture * m_image;
	float m_size;
	float m_Oldsize;
	Vec2 m_vPos;
	bool IsMouseDown;

	int State;
public:
	cButton(Vec2 vPos, cTexture * image);
	~cButton();
	
	void Init();
	bool Update();
	void Render();
	void Release();
};

