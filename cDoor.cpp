#include "DXUT.h"
#include "cDoor.h"


cDoor::cDoor(Dirction Dir)
	:StateDir(Dir)
{
	m_OpenImage = IMAGE->FindImage("Open_Door");
	m_CloseImage = IMAGE->FindImage("Close_Door");
	IsOpen = false;
	Init();
}


cDoor::~cDoor()
{
}

void cDoor::Init()
{

	switch (StateDir)
	{
	case LEFT:
		Angle = -90;
		m_vPos = Vec2(1180 , WINSIZEY / 2);
		m_rc = RECT{
			(LONG)(m_vPos.x - m_OpenImage->info.Height / 2),
			(LONG)(m_vPos.y - m_OpenImage->info.Width / 2),
			(LONG)(m_vPos.x + m_OpenImage->info.Height / 2),
			(LONG)(m_vPos.y + m_OpenImage->info.Width / 2)
		};
		break;
	case RIGHT:
		Angle = 90;
		m_vPos = Vec2(100, WINSIZEY / 2);
		m_rc = RECT{
			(LONG)(m_vPos.x - m_OpenImage->info.Height / 2),
			(LONG)(m_vPos.y - m_OpenImage->info.Width / 2),
			(LONG)(m_vPos.x + m_OpenImage->info.Height / 2),
			(LONG)(m_vPos.y + m_OpenImage->info.Width / 2)
		};
		break;
	case TOP:
		Angle = 0;
		m_vPos = Vec2(WINSIZEX / 2, 100);
		m_rc = RECT{
	        (LONG)(m_vPos.x - m_OpenImage->info.Width / 2),
	        (LONG)(m_vPos.y - m_OpenImage->info.Height / 2),
	        (LONG)(m_vPos.x + m_OpenImage->info.Height / 2),
	        (LONG)(m_vPos.y + m_OpenImage->info.Width / 2)
		};
		break;
	case BOTTOM:
		Angle = 180;
		m_vPos = Vec2(WINSIZEX / 2, 620);
		m_rc = RECT{
	        (LONG)(m_vPos.x - m_OpenImage->info.Width / 2),
	        (LONG)(m_vPos.y - m_OpenImage->info.Height / 2),
	        (LONG)(m_vPos.x + m_OpenImage->info.Width / 2),
	        (LONG)(m_vPos.y + m_OpenImage->info.Height / 2)
		};
		break;
	default:
		break;
	}
}

bool cDoor::Update(bool open, Vec2 PlayerPos)
{
	IsOpen = open;
	if (PlayerPos.x > m_rc.left &&
		PlayerPos.y > m_rc.top &&
		PlayerPos.x < m_rc.right &&
		PlayerPos.y < m_rc.bottom && IsOpen) {
		return true;
	}
	return false;
}

void cDoor::Render()
{
	if (IsOpen)
		IMAGE->Render(m_OpenImage, m_vPos, Angle, true);
	else
		IMAGE->Render(m_CloseImage, m_vPos, Angle, true);
}
