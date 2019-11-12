#pragma once

class cMap
{
private:
	struct Node
	{
		Vec2 vMatrix;
		bool IsOpen = true;
		int F = 0; //비용
		int G = 0; //시작점에서 부터 새로운 사각형까지의 비용
		int H = 0; //얻어진 사각형으로부터 최종까지의 비용

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

