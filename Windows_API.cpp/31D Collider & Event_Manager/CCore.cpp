#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDc(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDc);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 크기 조정
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); 

	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDc = GetDC(m_hWnd);   

	m_hBit = CreateCompatibleBitmap(m_hDc, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDc);

	HBITMAP h01dBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(h01dBit);

	// 자주 사용 할 펜 및 브러쉬 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::Getinst()->init();
	CTimeMgr::Getinst()->init();
	CKeyMgr::Getinst()->init();
	CSceneMgr::Getinst()->init();
	//CCollisionMgr::Getinst()->init();

	return S_OK;
}

void CCore::progress()
{
	static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}

	// ================
	// Manager update
	// ================

	CTimeMgr::Getinst()->update();
	CKeyMgr::Getinst()->update();

	// =============
	// Scene Update
	// =============

	CSceneMgr::Getinst()->update();

	// 충돌 체크
	CCollisionMgr::Getinst()->update();

	// ==========
	// Rendering
	// ==========
	
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::Getinst()->render(m_memDC);

	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::Getinst()->render();

	// ================
	// 이벤트 지연처리
	// ================

	CEventMgr::Getinst()->update();
}

void CCore::CreateBrushPen()
{
	// Hollow Brush
	// delete할 필요 없다.
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// Red Blue Green Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

