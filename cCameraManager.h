#pragma once
#include "singleton.h"
class cCameraManager : public singleton<cCameraManager>
{
private:
	D3DXMATRIX m_matProj, m_matView;
	Vec3 m_vCameraPos, m_vViewPos, m_vScrollPos, m_vFollowPos, m_vOldPos;
	bool b_Move;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void SetPosition(Vec3 pos) { b_Move = false; m_vCameraPos = pos; };
	void Follow(Vec3 pos) { m_vFollowPos = pos; b_Move = true; m_vOldPos = m_vCameraPos; }

	void Init();
	void Update();
	void SetTramsform();

	Vec2 GetCameraPos() { return m_vCameraPos; }
	Vec2 GetScrollPos() { return m_vScrollPos; }
};

#define CAMERA cCameraManager::GetInstance()
