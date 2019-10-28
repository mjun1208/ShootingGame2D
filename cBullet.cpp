#include "DXUT.h"
#include "cBullet.h"

#include "cMap.h"

cBullet::cBullet(Vec2 Pos, int Dir)
	:m_vPos(Pos) , DirState(Dir)
{
}


cBullet::~cBullet()
{
}

void cBullet::CheckColl(cMap * map)
{
	for (auto iter : map->GetTile()) {
	    if (m_vPos.x + 5 > iter->Getrc().left &&
	    	m_vPos.y + 5 > iter->Getrc().top &&
	    	m_vPos.x - 5 < iter->Getrc().right &&
	    	m_vPos.y - 5 < iter->Getrc().bottom &&
			!iter->GetDel()) {
		    if (iter->GetState() == Pumpkin || iter->GetState() == WoodBox)
				b_Del = true;
			if (iter->GetState() == Pumpkin) {
				iter->SetDel(true);
			}
	    	break;
	    }
		
	}
}
