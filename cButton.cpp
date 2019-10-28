#include "DXUT.h"
#include "cButton.h"


cButton::cButton(Vec2 vPos, cTexture * image)
	: m_vPos(vPos), m_image(image)
{
	m_size = 1.f;
	m_Oldsize = 1.f;
	State = Normal;
	IsMouseDown = false;
	Init();
}


cButton::~cButton()
{
}

void cButton::Init()
{
	m_rc = RECT{
		(LONG)(m_vPos.x - m_image->info.Width / 2), 
		(LONG)(m_vPos.y - m_image->info.Height / 2),
		(LONG)(m_vPos.x + m_image->info.Width / 2),
		(LONG)(m_vPos.y + m_image->info.Height / 2)
	};
}

bool cButton::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	if (PtInRect(&m_rc, pt)) {
		if (INPUT->MouseLPress()) {
			IsMouseDown = true;
			State = Click;
		}
		else
			State = OnCursor;
	}
	else {
		State = Normal;
		IsMouseDown = false;
	}

	if (IsMouseDown && INPUT->MouseLUp())
		return true;

	switch (State)
	{
	case Normal:
		m_size = 1.f;
		IsMouseDown = false;
		break;
	case OnCursor:
		m_size = 1.3f;
		break;
	case Click:
		m_size = 1.5f;
		break;
	default:
		break;
	}

	m_Oldsize = Lerp(m_Oldsize, m_size, 0.2f);

	return false;
}

void cButton::Render()
{
	IMAGE->ReBegin(true);
	IMAGE->Render(m_image, m_vPos, Vec3(m_Oldsize, m_Oldsize, m_Oldsize), 0, D3DCOLOR_XRGB(255, 255, 255), true);
	IMAGE->ReBegin(false);
}

void cButton::Release()
{
}

