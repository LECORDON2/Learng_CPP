#pragma once

#include "pch.h"

// singleton 매크로
#define SINGLE(type) public: static type* Getinst() { static type mgr; return &mgr; } private: type(); ~type();

#define DT CTimeMgr::Getinst()->GetDT()
