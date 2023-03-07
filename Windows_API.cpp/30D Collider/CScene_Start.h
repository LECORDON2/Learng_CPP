#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene // 상속 받음
{

public:
    virtual void Enter(); 
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();
};
