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
	QueryPerformanceCounter(&m_LLPrevCount);

	QueryPerformanceFrequency(&m_LLFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_LLCurCount);

	m_dDT = (double)(m_LLCurCount.QuadPart - m_LLPrevCount.QuadPart) / (double)m_LLFrequency.QuadPart;

	m_LLPrevCount = m_LLCurCount;

#ifdef _DEBUG // 디버깅 시에만 작동되는 전처리기(구성속성)
	if (m_dDT > (1. / 60.))
	{
		m_dDT = (1. / 60.);
	}
#endif
	
}

void CTimeMgr::render()
{
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
