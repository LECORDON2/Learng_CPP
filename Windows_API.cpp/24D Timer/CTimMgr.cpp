#include "pch.h"
#include "CTimeMgr.h"
#include <iostream>
#include "CCore.h"


CTimeMgr::CTimeMgr()
	:m_LLCurCount{}
	, m_LLFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 카운트
	// GetTickcount와 비슷하나 단위가 천만 
	QueryPerformanceCounter(&m_LLPrevCount);

	// 초당 카운트 횟수
	// 1초가 벌어졌을 때 count 값 차이가 얼마나 나는지도 구해와야 한다.
	QueryPerformanceFrequency(&m_LLFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_LLCurCount);

	// QuadPart이 실제 long long 타입의 자료형
	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_LLCurCount.QuadPart - m_LLPrevCount.QuadPart) / (double)m_LLFrequency.QuadPart;

	// 이전 카운트 값을 현재 값으로 갱신(다음번 계산을 위해서)
	m_LLPrevCount = m_LLCurCount;

	m_dAcc += m_dDT; // DT 누적

	++m_iCallCount;
	if (m_dAcc >= 1.) // 1초 누적
	{
		m_iFPS = m_iCallCount;

		m_dAcc = 0.;

		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %lf", m_iFPS, m_dDT);
		SetWindowText(CCore::Getinst()->GetMainHwnd(), szBuffer);
	}
}
