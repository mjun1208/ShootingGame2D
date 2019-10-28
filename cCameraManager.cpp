#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Init()
{
	m_vCameraPos = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0);
	m_vViewPos = Vec3(WINSIZEX, WINSIZEY, 0);
	m_vFollowPos = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0);
	m_vOldPos = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0);

	D3DXMatrixOrthoLH(&m_matProj, m_vViewPos.x, -m_vViewPos.y, 0, 1);
	g_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);

	b_Move = false;

}

void cCameraManager::Update()
{
	m_vScrollPos = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0) - m_vCameraPos;
	if (b_Move) {
		Vec3 MyPos = m_vCameraPos;
		Vec3 vDir = m_vFollowPos - MyPos;

		float fDistance = D3DXVec3Length(&vDir);

		if (fDistance < 1200.f) {
			m_vOldPos = m_vOldPos + (m_vFollowPos - m_vOldPos) * 0.4f;

			m_vCameraPos.x = m_vOldPos.x;
			m_vCameraPos.y = m_vOldPos.y;

		}
		else {
			m_vCameraPos = m_vFollowPos;
			b_Move = false;
		}
	}

	this->m_matView = D3DXMATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-m_vCameraPos.x, -m_vCameraPos.y, 0, 1);

}

void cCameraManager::SetTramsform()
{
	g_Device->SetTransform(D3DTS_VIEW, &m_matView);
}
