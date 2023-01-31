#pragma once

#include "pch.h"

// 매크로 함수
// 매크로는 코드를 치환하는 것
// #define Add(a, b) a + b
// 주의 * int c = 100 * Add(10, 20) = 120 이 나온다.

// singleton 매크로
#define SINGLE(type) public: static type* Getinst() { static type mgr; return &mgr; }
// \ 를 통해서 가독성 개선
//#define SINGLE(type) static type* Getinst()\ 
//                     {\
//                         static type mgr; \
//                         return &mgr; \
//                     }

//static CCore* Getinst()
//{
//	static CCore core;
//	return &core;
//}
