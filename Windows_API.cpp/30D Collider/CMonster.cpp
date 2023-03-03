#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
	CreateCollider();
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurpos = GetPos();

	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurpos.x += FDT * m_fSpeed * m_iDir;

	// 배회 거리 기준량을 넘어섰는지 확인

	float fDist = abs(m_vCenterPos.x - vCurpos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// 방향 변경
		m_iDir *= -1;
		vCurpos.x += fDist * m_iDir;
	}
	SetPos(vCurpos);
}
