#pragma once
#include "cBullet.h"
class cPlayerBullet : public cBullet
{
private:

public:
	cPlayerBullet(Vec2 Pos, int Dir);
	virtual ~cPlayerBullet();

	virtual void Update() override;
	virtual void Render() override;
};

