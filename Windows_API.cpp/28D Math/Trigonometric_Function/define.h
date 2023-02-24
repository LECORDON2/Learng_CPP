#pragma once

#include "pch.h"

// singleton 매크로
#define SINGLE(type) public: static type* Getinst() { static type mgr; return &mgr; } private: type(); ~type();

#define FDT CTimeMgr::Getinst()->GetfDT()
#define DT CTimeMgr::Getinst()->GetDT()

#define KEY_CHECK(key, state) CKeyMgr::Getinst()->GeyKEyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define PI 3.1415926535f

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
