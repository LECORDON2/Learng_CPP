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
	, m_hBit(0)
	, m_memDC(0)
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDc);

	// 이렇게 생성된 DC는 DeleteDC로 지워야 한다.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다
	m_hBit = CreateCompatibleBitmap(m_hDc, m_ptResolution.x, m_ptResolution.y);

	m_memDC = CreateCompatibleDC(m_hDc);

	HBITMAP h01dBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(h01dBit);

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
	CKeyMgr::Getinst()->update();
	update();

	render();
}

// 물체들의 변경점을 체크하는 곳
void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (CKeyMgr::Getinst()->GeyKEyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * CTimeMgr::Getinst()->GetDT();
	}
	if (CKeyMgr::Getinst()->GeyKEyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * CTimeMgr::Getinst()->GetDT();
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	 
	
	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC,int(vPos.x - vScale.x / 2.f)
		           ,int(vPos.y - vScale.y / 2.f)
		           ,int(vPos.x + vScale.x / 2.f)
		           ,int(vPos.y + vScale.y / 2.f));

	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
