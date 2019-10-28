#include "DXUT.h"
#include "cPlayerBullet.h"


cPlayerBullet::cPlayerBullet(Vec2 Pos, int Dir)
	: cBullet(Pos, Dir)
{
	m_image = IMAGE->FindImage("Player_Bullet");

	b_Del = false;
	f_LifeTime = 2;
	f_CheckTime = 0;
}


cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	f_CheckTime += DX_Time;
	switch (DirState)
	{
	case LEFT:
		m_vDir = Vec2(-1, 0);
		break;
	case TOP:
		m_vDir = Vec2(0, -1);
		break;
	case RIGHT:
		m_vDir = Vec2(1, 0);
		break;
	case BOTTOM:
		m_vDir = Vec2(0, 1);
		break;
	case FOLLOW:
	default:
		break;
	}

	m_vPos += m_vDir * 12;

	if (f_CheckTime >= f_LifeTime)
		b_Del = true;
}

void cPlayerBullet::Render()
{
	IMAGE->Render(m_image, m_vPos, 0, true);
}
