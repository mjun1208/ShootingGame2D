#pragma once
enum TileState {
	WoodBox, Pumpkin, Stage1_0 , Stage1_1 , None
};
class cTile
{
private:
	RECT rc;
	RECT Collrc;
	Vec2 vMatrix;
	TileState State;
	cTexture * m_image;
	cTexture * m_BreakImage;
	cTexture * m_HatImage;
	cTexture * m_BreakHatImage;
	Vec2 vPos;
	bool b_Del;
	bool b_IsFrameEnd;

	cFrame * m_Frame;
	cFrame * m_BreakFrame;
	cFrame * m_HatFrame;
	cFrame * m_BreakHatFrame; 
	void SetImage();
	void SetFrame();
public:
	cTile(RECT rc, Vec2 matrix , TileState state ,Vec2 pos);
	~cTile();
	
	void Init();
	void Update();
	void Render();
	void HatRender();
	void Release();


	Vec2 GetPos() { return vPos; }
	RECT Getrc() { return rc; }
	Vec2 GetMatrix() { return vMatrix; }
	RECT GetCollrc() { return Collrc; }
	
	TileState GetState() { return State; }
	void SetState(int state) { Release();  State = (TileState)state; SetImage(); Init(); SetFrame(); }

	bool GetDel() { return b_Del; }
	void SetDel(bool del) { b_Del = del; }
};

