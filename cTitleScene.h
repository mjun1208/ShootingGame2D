#pragma once
#include "cScene.h"
class cTitleScene : public cScene
{
private:
	cButton * m_TestButton;
	cTexture* m_BackGround;
	cButton * m_StartButton;
	cButton * m_CreditsButton;
	cButton * m_ExitButton;
	cButton * m_OptionButton;
	cButton * m_MakeMap;

public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

