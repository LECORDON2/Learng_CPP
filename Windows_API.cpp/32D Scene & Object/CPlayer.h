#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
    // 굳이 복사 생성자를 만들었을때
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin) // 내가만든 버전의 object 복사 생성자가 들어간다.
    //    , m_pTex(_origin.m_pTex)
    //{}
};
