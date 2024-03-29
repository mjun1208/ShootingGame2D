#include "DXUT.h"
#include "cEnemy.h"

#include "cMap.h"

cEnemy::cEnemy(cMap * map, Vec2 Pos)
	: m_vPos(Pos)
{
	Init(map);
}


cEnemy::~cEnemy()
{
}

void cEnemy::Init(cMap * map)
{
	m_Image = IMAGE->FindImage("Enemy");
	//m_vPos = Vec2(11, 1);
	m_vDir = Vec2(0, 0);
	m_vTarget = Vec2(0, 0);
	NowPath = 0;
	IsMove = false;

	for (auto iter : map->GetTile()) {
		if (iter->GetMatrix() == m_vPos) {
			m_vPos = iter->GetPos();
		}
	}

	m_rc = {
		(LONG)(m_vPos.x - m_Image->info.Width / 2),(LONG)(m_vPos.y - m_Image->info.Height / 2),(LONG)(m_vPos.x + m_Image->info.Width / 2),(LONG)(m_vPos.y + m_Image->info.Height / 2)
	};

	b_Del = false;
	i_Hp = 3;
}

void cEnemy::Update(Vec2 Target, cMap * map)
{
	Movement(Target, map);
	CheckColl(map);
	m_rc = {
		(LONG)(m_vPos.x - m_Image->info.Width / 2),(LONG)(m_vPos.y - m_Image->info.Height / 2),(LONG)(m_vPos.x + m_Image->info.Width / 2),(LONG)(m_vPos.y + m_Image->info.Height / 2)
	};

	if (i_Hp <= 0)
		b_Del = true;
}

void cEnemy::Render()
{
	IMAGE->Render(m_Image, m_vPos, 0, true);
}

void cEnemy::Release()
{
}

void cEnemy::Movement(Vec2 Target, cMap * map)
{
	if (map->FindPath(map->GetMatrix(m_vPos), map->GetMatrix(Target)).size() > 0) {
		IsMove = true;
	}
	else
		IsMove = false;

	if (IsMove) {
		m_vDir = Vec2(0, 0);

		Vec2 Dir;
		if (map->GetMatrix(m_vPos) == map->GetMatrix(Target)) {
			Dir = Target - m_vPos;
			m_vTarget = Target;
		}
		else {
			if (m_vLastTargetPos != map->GetMatrix(Target)) {
				NowPath = 1;
				m_vLastTargetPos = map->GetMatrix(Target);
			    Path = map->FindPath(map->GetMatrix(m_vPos), map->GetMatrix(Target));
			}

			m_vTarget = Path[NowPath];

			for (auto iter : map->GetTile()) {
				if (iter->GetMatrix() == m_vTarget) {
					m_vTarget = iter->GetPos();
				}
			}
			
			if (m_vPos.x - 10 < m_vTarget.x &&
				m_vPos.y - 10 < m_vTarget.y &&
				m_vPos.x + 10 > m_vTarget.x &&
				m_vPos.y + 10 > m_vTarget.y) {
				++NowPath;
			}

			Dir = m_vTarget - m_vPos;
		}
		D3DXVec2Normalize(&Dir, &Dir);
		m_vDir += Dir;
	}
	if (INPUT->KeyDown('Z'))
		map->FindPath(map->GetMatrix(m_vPos), map->GetMatrix(Target));
}

void cEnemy::CheckColl(cMap * map)
{
	Vec2 movePos;
	bool Once = true;
	movePos = m_vPos + (m_vDir * 4);

	RECT InterRect;
	int InterW = 0;
	int InterH = 0;

	int ChangerW = 0;
	int ChangerH = 0;


	RECT rc = {
		(LONG)(movePos.x - m_Image->info.Width / 2),(LONG)(movePos.y - 2),(LONG)(movePos.x + m_Image->info.Width / 2),(LONG)(movePos.y + 2)
	};
	for (auto iter : map->GetTile()) {
		if (iter->GetState() != None) {
			//if (movePos.x + 35 > iter->GetCollrc().left &&
			//	movePos.y > iter->GetCollrc().top &&
			//	movePos.x - 35 < iter->GetCollrc().right &&
			//	movePos.y < iter->GetCollrc().bottom) {
			//	CanGo = false;
			//}
			if (IntersectRect(&InterRect, &rc, &iter->GetCollrc())) {
				InterW = InterRect.right - InterRect.left;
				InterH = InterRect.bottom - InterRect.top;

				if (InterW > InterH) {
					if (InterRect.top == iter->GetCollrc().top) {
						ChangerH = -InterH;
					}
					else if (InterRect.bottom == iter->GetCollrc().bottom) {
						ChangerH = InterH;
					}
				}
				else {
					if (InterRect.left == iter->GetCollrc().left) {
						ChangerW = -InterW;
					}
					else if (InterRect.right == iter->GetCollrc().right) {
						ChangerW = InterW;
					}
				}
			}
		}
	}

	//DEBUG_LOG(m_vDir.x << " " << m_vDir.y);

	m_vPos += m_vDir * 4;

	if (abs(ChangerH) == abs(ChangerW))
		ChangerW /= 2;

	if (InterH != 0) {
		m_vPos.y += ChangerH * 2;
	}
	if (InterW != 0) {
		m_vPos.x += ChangerW * 2;
	}
}