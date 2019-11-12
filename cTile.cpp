#include "DXUT.h"
#include "cTile.h"


void cTile::SetImage()
{
	switch (State)
	{
	case WoodBox:
		m_image = IMAGE->FindImage("WoodBox");
		m_HatImage = IMAGE->FindImage("WoodBox_Hat");
		m_BreakImage = nullptr;
		m_BreakHatImage = nullptr;
		break;
	case Pumpkin:
		m_image = IMAGE->FindImage("Pumpkin");
		m_HatImage = IMAGE->FindImage("Pumpkin_Hat");
		m_BreakImage = IMAGE->FindImage("Pumpkin_Break");
		m_BreakHatImage = IMAGE->FindImage("Pumpkin_BreakHat");
		break;
	case Stage1_0:
		m_image = IMAGE->FindImage("Stage1_0");
		m_HatImage = IMAGE->FindImage("Stage1_0_Hat");
		m_BreakImage = nullptr;
		m_BreakHatImage = nullptr;
		break;
	case Stage1_1:
		m_image = IMAGE->FindImage("Stage1_1");
		m_HatImage = IMAGE->FindImage("Stage1_1_Hat");
		m_BreakImage = nullptr;
		m_BreakHatImage = nullptr;
		break;
	case None:
		m_image = IMAGE->FindImage("None");
		m_HatImage = nullptr;
		m_BreakImage = nullptr;
		m_BreakHatImage = nullptr;
	default:
		break;
	}
}

void cTile::SetFrame()
{
	m_Frame = new cFrame();
	m_Frame->SetFrame(0, m_image->GetLength(), 50);

	if (m_BreakImage) {
		m_BreakFrame = new cFrame();
		m_BreakFrame->SetFrame(0, m_BreakImage->GetLength(), 60);
	}
	if (m_HatImage) {
		m_HatFrame = new cFrame();
		m_HatFrame->SetFrame(0, m_HatImage->GetLength(), 50);
	}
	if (m_BreakHatImage) {
		m_BreakHatFrame = new cFrame();
		m_BreakHatFrame->SetFrame(0, m_BreakHatImage->GetLength(), 60);
 	}
}

cTile::cTile(RECT rc, Vec2 matrix, TileState state, Vec2 pos)
	: rc(rc), vMatrix(matrix) , State(state), vPos(pos)
{
	SetImage();
	Init();
	SetFrame();
}


cTile::~cTile()
{
	Release();
}

void cTile::Init()
{
	b_Del = false;
	b_IsFrameEnd = false;

    rc = {
		(LONG)vMatrix.x * 100,
		(LONG)vMatrix.y * 100,
		(LONG)(vMatrix.x * 100) + 100,
		(LONG)(vMatrix.y * 100) + 100
	};

	vPos = Vec2(vMatrix.x * 100 + 50, vMatrix.y * 100 + 50);
	
	Collrc = {
		(LONG)(vPos.x - m_image->FindImage(0)->info.Width + 50),
		(LONG)(vPos.y - m_image->FindImage(0)->info.Height + (m_image->FindImage(0)->info.Height - 40) ),
		(LONG)(vPos.x + m_image->FindImage(0)->info.Width / 2),
		(LONG)(vPos.y + 50)
	};
}

void cTile::Update()
{
	m_Frame->Frame();
	
	if (m_HatImage)
		m_HatFrame->Frame();

	if (b_Del) {
		if (m_BreakImage) {
			m_BreakFrame->Frame();
			if (m_BreakHatImage)
				m_BreakHatFrame->Frame();
			if (m_BreakFrame->NowFrame == m_BreakFrame->EndFrame) {
				b_IsFrameEnd = true;
			}
			if (m_BreakFrame->NowFrame == m_BreakFrame->StartFrame && b_IsFrameEnd) {
				SetState(None);
				b_Del = false;
			}
		}
		else
		{
			SetState(None);
			b_Del = false;
		}
	}
}

void cTile::Render()
{
	if (State != None && !b_Del)
	IMAGE->CenterRender(m_image->FindImage(m_Frame->NowFrame), vPos, 
		Vec3(m_image->FindImage(m_Frame->NowFrame)->info.Width / 2, m_image->FindImage(m_Frame->NowFrame)->info.Height - 50, 0), 0);
	else if (b_Del && m_BreakImage)
		IMAGE->CenterRender(m_BreakImage->FindImage(m_BreakFrame->NowFrame), vPos,
			Vec3(m_BreakImage->FindImage(m_BreakFrame->NowFrame)->info.Width / 2, m_BreakImage->FindImage(m_BreakFrame->NowFrame)->info.Height - 50, 0), 0);
}

void cTile::HatRender()
{
	if (m_HatImage && State != None && !b_Del)
		IMAGE->CenterRender(m_HatImage->FindImage(m_HatFrame->NowFrame), Vec2(vPos.x, vPos.y + 10),
			Vec3(m_HatImage->FindImage(m_HatFrame->NowFrame)->info.Width / 2, m_HatImage->FindImage(m_HatFrame->NowFrame)->info.Height, 0), 0);
	else if (b_Del && m_BreakHatImage)
		IMAGE->CenterRender(m_BreakHatImage->FindImage(m_BreakHatFrame->NowFrame), Vec2(vPos.x, vPos.y + 10),
			Vec3(m_BreakHatImage->FindImage(m_BreakHatFrame->NowFrame)->info.Width / 2, m_BreakHatImage->FindImage(m_BreakHatFrame->NowFrame)->info.Height, 0), 0);
}

void cTile::Release()
{
	SAFE_DELETE(m_Frame);
	if (m_BreakImage)
		SAFE_DELETE(m_BreakFrame);
	if (m_HatImage) 
		SAFE_DELETE(m_HatFrame)
	if (m_BreakHatImage)
		SAFE_DELETE(m_BreakHatFrame);
}
