#include "DXUT.h"
#include "cMap.h"


cMap::cMap(int Map)
	: Map(Map)
{
}


cMap::~cMap()
{
	Release();
}

void cMap::Init()
{
    //MapSet->Release();
	MapSet->LoadInfo(Map);
	for (auto iter : MapSet->OutInfo()) {
		Tiles.push_back(new cTile(iter->Getrc(), iter->GetMatrix(), iter->GetState(), iter->GetPos()));
	}
	MapSet->Release();
	//Tiles = MapSet->OutInfo();
	for (auto iter : Tiles)
		iter->Init();

}

void cMap::Update()
{
	for (auto iter : Tiles)
		iter->Update();
}

void cMap::BackGroundRender()
{
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 8; j++) {
			IMAGE->Render(IMAGE->FindImage("Stage1_BackGroundTile"), Vec2(i * 100 + 50, j * 100 + 50), 0, true);
		}
	}
}

void cMap::Render()
{
	for (int i = 0; i < 8; i++) {
		for (auto iter : Tiles) {
			if (iter->GetMatrix().y == i)
				iter->Render();
		}
	}
}

void cMap::HatRender()
{
	for (int i = 0; i < 8; i++) {
		for (auto iter : Tiles) {
			if (iter->GetMatrix().y == i)
				iter->HatRender();
		}
	}
}

void cMap::Release()
{
	for (auto iter : Tiles)
		SAFE_DELETE(iter);
	Tiles.clear();
	MapSet->Release();
}

Vec2 cMap::GetMatrix(Vec2 pos)
{
	POINT pt;
	pt.x = pos.x;
	pt.y = pos.y;

	for (auto iter : Tiles) {
		if (PtInRect(&iter->Getrc(), pt)) {
			return iter->GetMatrix();
		}
	}
	return Vec2(0,0);
}

int cMap::GetState(Vec2 matrix)
{
	for (auto iter : Tiles) {
		if (matrix == iter->GetMatrix()) {
			return iter->GetState();
		}
	}
	return 0;
}

vector<Vec2> cMap::FindPath(Vec2 MyMatrix, Vec2 TargetMatrix)
{
	vector<Node*> OpenPath;
	vector<Node*> ClosePath;
	vector<Node*> AddOpenPath;
	Node * NowPath;
	Node * Path[8]; // 0 = 위, 1 = 아래, 2 = 왼쪽, 3 = 오른쪽,
	                  // 4 = 위.왼 , 5 = 위.오 , 6 = 아.왼, 7 = 아.오

	bool IsNoTarget = false;

	for (int i = 0; i < 8; i++) {
		Path[i] = new Node;
	}
	NowPath = new Node{ MyMatrix , true, 0, 0, 0 };
	
	while (true) {
		ClosePath.push_back(new Node{ NowPath->vMatrix ,NowPath->IsOpen ,NowPath->F , NowPath->G , NowPath->H, NowPath->IsAlready, NowPath->ParentMatrix });
		if (NowPath->vMatrix == TargetMatrix)
			break;

		Path[0]->vMatrix = Vec2(NowPath->vMatrix.x, NowPath->vMatrix.y - 1);
		Path[1]->vMatrix = Vec2(NowPath->vMatrix.x, NowPath->vMatrix.y + 1);
		Path[2]->vMatrix = Vec2(NowPath->vMatrix.x - 1, NowPath->vMatrix.y);
		Path[3]->vMatrix = Vec2(NowPath->vMatrix.x + 1, NowPath->vMatrix.y);
		Path[4]->vMatrix = Vec2(NowPath->vMatrix.x - 1, NowPath->vMatrix.y - 1);
		Path[5]->vMatrix = Vec2(NowPath->vMatrix.x + 1, NowPath->vMatrix.y - 1);
		Path[6]->vMatrix = Vec2(NowPath->vMatrix.x - 1, NowPath->vMatrix.y + 1);
		Path[7]->vMatrix = Vec2(NowPath->vMatrix.x + 1, NowPath->vMatrix.y + 1);

		for (int i = 0; i < 8; i++) {
			Path[i]->ParentMatrix = NowPath->vMatrix;
			Path[i]->IsOpen = true;
			Path[i]->IsAlready = false;

			int G = NowPath->G;

			if (i <= 3)
				Path[i]->G = G + 10;
			else
				Path[i]->G = G + 14;

			Vec2 Sum;
			Sum = TargetMatrix - Path[i]->vMatrix;
			Path[i]->H = (abs(Sum.x) + abs(Sum.y)) * 10;

			Path[i]->F = Path[i]->G + Path[i]->H;
		}


		for (int i = 0; i < 8; i++) {

			for (auto iter : ClosePath) {
				if (iter->vMatrix == Path[i]->vMatrix)
					Path[i]->IsOpen = false;
			}

			if (GetState(Path[i]->vMatrix) != None) {
				Path[i]->IsOpen = false;

				switch (i)
				{
				case 0:
					Path[4]->IsOpen = false;
					Path[5]->IsOpen = false;
					break;
				case 1:
					Path[6]->IsOpen = false;
					Path[7]->IsOpen = false;
					break;
				case 2:
					Path[4]->IsOpen = false;
					Path[6]->IsOpen = false;
					break;
				case 3:
					Path[5]->IsOpen = false;
					Path[7]->IsOpen = false;
					break;
				default:
					break;
				}
			}
		}


		for (int i = 0; i < 8; i++) {
			bool b_CanOpen = true;
			bool b_Cange = false;
			for (auto iter : OpenPath) {
				if (Path[i]->vMatrix == iter->vMatrix) {
					if (Path[i]->G < iter->G) {
						b_Cange = true;
					}
					else {
						b_CanOpen = false;
					}
				}
			}
			if (Path[i]->IsOpen && !Path[i]->IsAlready && b_CanOpen && !b_Cange) {
				//Node * Temp = Path[i];
				OpenPath.push_back(new Node{ Path[i]->vMatrix ,Path[i]->IsOpen ,Path[i]->F , Path[i]->G , Path[i]->H, Path[i]->IsAlready, Path[i]->ParentMatrix });
			}
			else if (Path[i]->IsOpen && !Path[i]->IsAlready && b_CanOpen && b_Cange) {
				for (auto iter = OpenPath.begin(); iter != OpenPath.end();) {
					if ((*iter)->vMatrix == Path[i]->vMatrix)
					{
						SAFE_DELETE(*iter);
						iter = OpenPath.erase(iter);
					}
					else
						++iter;
				}

				//Node * Temp = Path[i];
				OpenPath.push_back(new Node{ Path[i]->vMatrix ,Path[i]->IsOpen ,Path[i]->F , Path[i]->G , Path[i]->H, Path[i]->IsAlready, Path[i]->ParentMatrix });
			}
		}

		int Min_F = 99999;
		for (auto Closeiter : ClosePath) {
			for (auto Openiter : OpenPath) {
				if (Openiter->IsOpen && Min_F > Openiter->F && Closeiter->vMatrix != Openiter->vMatrix) {
					Min_F = Openiter->F;
					//NowPath = iter;  //누수 O, 에러 X , 부모 에러 o
					SAFE_DELETE(NowPath); //누수 X , 에러 O , 부모 에러 x
					NowPath = new Node{ Openiter->vMatrix ,Openiter->IsOpen ,Openiter->F , Openiter->G , Openiter->H, Openiter->IsAlready, Openiter->ParentMatrix };
				}
			}
		}
		//DEBUG_LOG(NowPath->vMatrix.x << " " << NowPath->vMatrix.y << " " << NowPath->F << " " << NowPath->G << " " << NowPath->H);

		if (OpenPath.size() == 0 && NowPath->vMatrix != TargetMatrix) {
			IsNoTarget = true;
			break;
		}

		for (auto iter = OpenPath.begin(); iter != OpenPath.end();) {
			if (NowPath->vMatrix == (*iter)->vMatrix) {
				SAFE_DELETE(*iter);
				iter = OpenPath.erase(iter);
			}
			else
				++iter;
		}
	}
	 
	SAFE_DELETE(NowPath);

	for (int i = 0; i < 8; i++) {
		SAFE_DELETE(Path[i]);
	}

	if (OpenPath.size() == 0 && IsNoTarget) {
		for (auto iter : OpenPath) {
			SAFE_DELETE(iter);
		}
		OpenPath.clear();

		for (auto iter : ClosePath)
			SAFE_DELETE(iter);
		ClosePath.clear();
		vector<Vec2> A;
		return A;
	}

	for (auto iter : OpenPath) {
		SAFE_DELETE(iter);
	}
	OpenPath.clear();

	return SavePath(ClosePath, MyMatrix, TargetMatrix);
}

vector<Vec2> cMap::SavePath(vector<Node*>& ClosePath, Vec2 MyMatrix, Vec2 TargetMatrix)
{
	vector<Vec2> ClosePathVec;
	vector<Vec2> FinalPathVec;

	Vec2 PathVec2[8];
	
	bool IsStartPath = true;

	Vec2 NowVec2;

	NowVec2 = TargetMatrix;
	ClosePathVec.push_back(TargetMatrix);

	reverse(ClosePath.begin(), ClosePath.end());
	for (auto iter : ClosePath) {
		if (iter->vMatrix == NowVec2 && NowVec2 != MyMatrix) {
			ClosePathVec.push_back(iter->ParentMatrix);
			NowVec2 = iter->ParentMatrix;
		}
	}
	reverse(ClosePathVec.begin(), ClosePathVec.end());
	

	for (auto iter : ClosePath)
		SAFE_DELETE(iter);
	ClosePath.clear();

	return ClosePathVec;
	// TODO: 여기에 반환 구문을 삽입합니다.
}
