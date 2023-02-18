#pragma once

#include "pch.h"

// singleton 매크로
#define SINGLE(type) public: static type* Getinst() { static type mgr; return &mgr; } private: type(); ~type();

#define FDT CTimeMgr::Getinst()->GetfDT()
#define DT CTimeMgr::Getinst()->GetDT()


enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};
