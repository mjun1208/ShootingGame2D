#pragma once
#include "cScene.h"
class cTitleScene : public cScene
{
private:
	cButton * m_TestButton;
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

