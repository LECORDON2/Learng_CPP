#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDc(0)
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDc);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
  
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); 

	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDc = GetDC(m_hWnd);   

	// Manager 초기화
	CTimeMgr::Getinst()->init();
	CKeyMgr::Getinst()->init();

	g_obj.SetPos(Vec2( (float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2 )));
	g_obj.SetScalse(Vec2(100, 100));

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

	// Manager update
	CTimeMgr::Getinst()->update();
	update();

	render();
}

// 물체들의 변경점을 체크하는 곳
void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		// 움직이는 양이 고정 값이면 컴퓨터 성능에 따라 속도에 차이가 날 수 있다.
		// 시간 동기화(컴퓨터 속도에 관계없이 초당 속도가 필요하다.)
		// vPos.x -= 0.01f; 
		vPos.x -= 100.f * CTimeMgr::Getinst()->GetDT();

	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * CTimeMgr::Getinst()->GetDT();
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDc,int(vPos.x - vScale.x / 2.f)
		           ,int(vPos.y - vScale.y / 2.f)
		           ,int(vPos.x + vScale.x / 2.f)
		           ,int(vPos.y + vScale.y / 2.f));
}
