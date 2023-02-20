#pragma once
#include "CObject.h"

class CMonster :
    public CObject
{
private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir;  // 진행 방향 정보 1(우), -1(좌)


public:
    float GetSpeed() { return m_fSpeed; }
    void  SetSpeed(float _f) { m_fSpeed = _f; }
    void  SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void  SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void update();

public:
    CMonster();
    ~CMonster();
};
