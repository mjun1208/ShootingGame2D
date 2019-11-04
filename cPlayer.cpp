#include "DXUT.h"
#include "cPlayer.h"

#include "cMap.h"

#include "cPlayerBullet.h"

cPlayer::cPlayer(vector<cBullet *>& Bullet)
	: m_Bullet(Bullet)
{
}


cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	m_Image = IMAGE->FindImage("Player");
	m_MoveImage[BOTTOM] = IMAGE->FindImage("Player_Move_Front");
	m_MoveImage[TOP] = IMAGE->FindImage("Player_Move_Back");
	m_MoveImage[LEFT] = IMAGE->FindImage("Player_Move_Left");
	m_MoveImage[RIGHT] = IMAGE->FindImage("Player_Move_Right");

	m_AttackImage[BOTTOM] = IMAGE->FindImage("Player_Attack_Front");
	m_AttackImage[TOP] = IMAGE->FindImage("Player_Attack_Back");
	m_AttackImage[LEFT] = IMAGE->FindImage("Player_Attack_Left");
	m_AttackImage[RIGHT] = IMAGE->FindImage("Player_Attack_Right");

	m_vDir = Vec2(0, 0);
	m_vPos = Vec2(150, 100);

	b_Move = false;
	b_Attack = false;
	b_EndAttackFrame = false;

	m_MoveFrame_3 = new cFrame();
	m_MoveFrame_3->SetFrame(0, 3, 50);

	m_MoveFrame_5 = new cFrame();
	m_MoveFrame_5->SetFrame(0, 5, 50);

	m_AttackFrame = new cFrame();
	m_AttackFrame->SetFrame(0, 3, 50);
}

void cPlayer::Update(cMap * map)
{
	Movement();
	CheckColl(map);

	if (m_vDir.x != 0 || m_vDir.y != 0)
		b_Move = true;
	else
		b_Move = false;

	if (b_Move) {
		m_MoveFrame_3->Frame();
		m_MoveFrame_5->Frame();
	}
	else {
		m_MoveFrame_3->NowFrame = 0;
		m_MoveFrame_5->NowFrame = 0;
	}

	if (b_Attack)
	{
		m_AttackFrame->Frame();
		if (m_AttackFrame->NowFrame == m_AttackFrame->EndFrame) {
			b_EndAttackFrame = true;
		}
		if (m_AttackFrame->NowFrame == m_AttackFrame->StartFrame && b_EndAttackFrame) {
			b_Attack = false;
			b_EndAttackFrame = false;
			m_AttackFrame->NowFrame = 0;
		}
	}
	else
		m_AttackFrame->NowFrame = 0;
	//DEBUG_LOG(map->GetMatrix(m_vPos).x << " " << map->GetMatrix(m_vPos).y);
}

void cPlayer::Render()
{
	//IMAGE->Render(m_Image, m_vPos, 0, true);

	if (b_Attack)
		IMAGE->Render(m_AttackImage[ShootDirState]->FindImage(m_AttackFrame->NowFrame), m_vPos, 0, true);
	else if (b_Move) {
		if(DirState == TOP || DirState == BOTTOM)
			IMAGE->Render(m_MoveImage[DirState]->FindImage(m_MoveFrame_3->NowFrame), m_vPos, 0, true);
		if (DirState == LEFT || DirState == RIGHT)
			IMAGE->Render(m_MoveImage[DirState]->FindImage(m_MoveFrame_5->NowFrame), m_vPos, 0, true);
	}
	else
		IMAGE->Render(m_Image, m_vPos, 0, true);
}

void cPlayer::Release()
{
	SAFE_DELETE(m_MoveFrame_3);
	SAFE_DELETE(m_MoveFrame_5);
	SAFE_DELETE(m_AttackFrame);
}

void cPlayer::CheckColl(cMap * map)
{
	Vec2 movePos;
	bool Once = true;
	movePos = m_vPos + (m_vDir * 5);

	RECT InterRect;
	int InterW = 0;
	int InterH = 0;

	int ChangerW = 0;
	int ChangerH = 0;


	RECT PlayerRect = {
		(LONG)(movePos.x - 35),(LONG)(movePos.y - 10),(LONG)(movePos.x + 35),(LONG)(movePos.y + 10)
	};

	for (auto iter : map->GetTile()) {
		if (iter->GetState() != None) {
			//if (movePos.x + 35 > iter->GetCollrc().left &&
			//	movePos.y > iter->GetCollrc().top &&
			//	movePos.x - 35 < iter->GetCollrc().right &&
			//	movePos.y < iter->GetCollrc().bottom) {
			//	CanGo = false;
			//}
			if (IntersectRect(&InterRect, &PlayerRect, &iter->Getrc())) {
				InterW = InterRect.right - InterRect.left;
				InterH = InterRect.bottom - InterRect.top;
				//iter->SetDel(true);
				if (InterW > InterH) {
					if (InterRect.top == iter->Getrc().top) {
						ChangerH = -InterH;
					}
					else if (InterRect.bottom == iter->Getrc().bottom) {
						ChangerH = InterH;
					}
				}
				else {
					if (InterRect.left == iter->Getrc().left) {
						ChangerW = -InterW;
					}
					else if (InterRect.right == iter->Getrc().right) {
						ChangerW = InterW;
					}
				}
			}
		}
	}

	//DEBUG_LOG(m_vDir.x << " " << m_vDir.y);

	m_vPos += m_vDir * 5;

	if (abs(ChangerH) == abs(ChangerW))
		ChangerW /= 2;

	if (InterH != 0) {
		m_vPos.y += ChangerH;
	}
	if (InterW != 0) {
		m_vPos.x += ChangerW;
	}
}

void cPlayer::ShootBullet(Dirction Dir)
{
	ShootDirState = Dir;
	m_Bullet.push_back(new cPlayerBullet(m_vPos, ShootDirState));
	b_Attack = true;
}

void cPlayer::Movement()
{
	m_vDir = Vec2(0, 0);
	if (INPUT->KeyPress('A')) {
		m_vDir.x --;
		DirState = LEFT;
	}
	if (INPUT->KeyPress('D')) {
		m_vDir.x ++;
		DirState = RIGHT;
	}
	if (INPUT->KeyPress('W')) {
		m_vDir.y --;
		DirState = TOP;
	}
	if (INPUT->KeyPress('S')) {
		m_vDir.y ++;
		DirState = BOTTOM;
	}

	if (INPUT->KeyPress(VK_UP) && !b_Attack) {
		ShootBullet(TOP);
	}
	else if (INPUT->KeyPress(VK_DOWN) && !b_Attack) {
		ShootBullet(BOTTOM);
	}
	else if (INPUT->KeyPress(VK_LEFT) && !b_Attack) {
		ShootBullet(LEFT);
	}
	else if (INPUT->KeyPress(VK_RIGHT) && !b_Attack) {
		ShootBullet(RIGHT);
	}
}
