#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene // 상속 받음
{

public:
    virtual void Enter(); //  virtual 은 쓰지않아도 되나 명시적으로 보여주기 위해서 적어준다.
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();
};
