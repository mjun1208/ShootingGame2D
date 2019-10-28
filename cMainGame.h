#pragma once
class cLoadScene;
class cTitleScene;
class cMapEditerScene;
class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render();
	void Release();

	void ResetDevice();
	void LostDevice();
};

