#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능


// 정적변수(데이터 영역)
// 1. 함수 안 (데이터 영역, 해당함수에서만 접근 가능)
// 2. 파일 안 (데이터 영역, 여러파일에서 같은 이름을 써도 에러 발생 안함)
// 3. 클래스 안 (데이터 영역, 클래스의 객체를 아무리 많이 만들어도 데이터 영역에 하나만 존재, 클래스 내부에서 접근 가능)

class CCore
{
// private:
//	 int m_i;
//	 static int m_iStatic;  // 정적 멤버(데이터 영역, 클래스의 객체를 아무리 많이 만들어도 데이터 영역에 하나만 존재, 클래스 내부에서 접근 가능)
//	                        // 이렇게 선언된 정적 멤버는 클래스 밖에서 반드시 초기화 해주어야 한다.
// public:         
//	 static int m_pStatic;  // 만약 public으로 선언하면 CCore::m_pStatic; 도 가능하다.
//	                        // 정적 멤버는 클래스 밖에서 반드시 초기화 해주어야 한다.
	                          
private:
	static CCore* g_pInst;

public:  // 그러나 객체가 없으면 멤버 함수를 호출할 수 없다. 그래서 객체가 없어도 되는 멤버 함수를 만든다.(static이 붙은 멤버 함수)
	// 정적 멤버함수
	static CCore* GetInstance()  // 그러나 정적 멤버 함수는 멤버에 접근할 수 없다. this를 받지 않는 함수이다.
	{
		// static CCore* pCore = nullptr;

		// 최초 호출 된 경우
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;

		}
		// 2번 이상 호출 된 경우 아무것도 안한다.

		return g_pInst;
	}

	static void Release()
	{
		// CCore* p = GetInstance(); 
		// delete p
		// 싱글톤 객체의 주소를 접근하기 위해 GetInstance를 사용한다.
		// 그러나 이렇게하면 싱글톤 객체를 삭제하고 다시 생성할 때 GetInstance가 이전에 삭제한 곳의 주소를 준다.
		// 그래서 클래스 안의 정적 멤버로 선언한다.

		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

	// 정적 멤버함수, 객체없이 호출 가능, this가 없다(멤버 접근 불가), 정적 멤버는 접근 가능

private:  // 객체를 한개만 만들기 위해서 생성자 소멸자를 private로 만듦, 그래서 객체를 만드는 멤버 함수를 만든다. 
	CCore();
	~CCore();
};


// 이렇게 선언된 정적 멤버는 클래스 밖에서 반드시 초기화 해주어야 한다.
// int CCore::m_pStatic = 0; 

CCore* pCore = CCore::GetInstance();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCore.cpp

#include "CCore.h"


CCore* CCore::g_pInst = nullptr;
