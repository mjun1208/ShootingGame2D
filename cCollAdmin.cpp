#include "DXUT.h"
#include "cCollAdmin.h"

#include "cEnemyAdmin.h"
#include "cBulletAdmin.h"

#include "cEnemy.h"
#include "cPlayerBullet.h"

cCollAdmin::cCollAdmin()
{
}


cCollAdmin::~cCollAdmin()
{
}

void cCollAdmin::Update(cEnemyAdmin * Enemy, cBulletAdmin * Bullet)
{
	Enemy_Bullet(Enemy, Bullet);
}

void cCollAdmin::Enemy_Bullet(cEnemyAdmin * Enemy, cBulletAdmin * Bullet)
{
	for (auto iter = Enemy->GetEnemy().begin(); iter != Enemy->GetEnemy().end();) {
		for (auto iter_ = Bullet->GetBullet().begin(); iter_ != Bullet->GetBullet().end();) {
			int InterW = 0;
			int InterH = 0;
			int ChangerH = 0;
			int ChangerW = 0;
			RECT InterRect;
			if (IntersectRect(&InterRect, &(*iter)->Getrc(), &(*iter_)->Getrc()) && !(*iter)->GetDel() && !(*iter_)->GetDel()) {
				InterW = InterRect.right - InterRect.left;
				InterH = InterRect.bottom - InterRect.top;

				if (InterW > InterH) {
					if (InterRect.top == (*iter_)->Getrc().top) {
						ChangerH = -InterH;
					}
					else if (InterRect.bottom == (*iter_)->Getrc().bottom) {
						ChangerH = InterH;
					}
				}
				else {
					if (InterRect.left == (*iter_)->Getrc().left) {
						ChangerW = -InterW;
					}
					else if (InterRect.right == (*iter_)->Getrc().right) {
						ChangerW = InterW;
					}
				}
				(*iter)->SetPos((*iter)->GetPos() + Vec2(ChangerW, ChangerH) * 2);
				(*iter)->SetHp((*iter)->GetHp() - 1);
				(*iter_)->SetDel(true);
			}
			++iter_;
		}
		++iter;
	}
}
