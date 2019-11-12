#pragma once

class cMap
{
private:
	struct Node
	{
		Vec2 vMatrix;
		bool IsOpen = true;
		int F = 0; //���
		int G = 0; //���������� ���� ���ο� �簢�������� ���
		int H = 0; //����� �簢�����κ��� ���������� ���

		bool IsAlready = false;

		Vec2 ParentMatrix;
	};
	int Map;
	int NowStage;
	cTexture * m_BackGround;
	int BackGroundArray[15][15];
private:
	vector<cTile*> Tiles;
public:
	cMap(int NowStage, int Map);
	~cMap();

	void Init();
	void Update();
	void BackGroundRender();
	void Render();
	void HatRender();
	void Release();
	vector<cTile*>& GetTile() { return Tiles; }

	Vec2 GetMatrix(Vec2 pos);
	int GetState(Vec2 matrix);

	vector<Vec2> FindPath(Vec2 MyMatrix, Vec2 TargetMatrix);
	vector<Vec2> SavePath(vector<Node*>& ClosePath , Vec2 MyMatrix, Vec2 TargetMatrix);
};

