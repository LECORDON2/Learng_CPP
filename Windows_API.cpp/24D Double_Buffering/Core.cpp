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

	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); 

	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDc = GetDC(m_hWnd);   

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다
  
  // 작업영역의 픽셀을 묶어서 Bitmap이라고 부른다.
	// 같은 해상도의 비트맵을 호환성을 고려하여 만든다. 비트맵 핸들도 받는다.(m_hBit)
	m_hBit = CreateCompatibleBitmap(m_hDc, m_ptResolution.x, m_ptResolution.y);
	// 만든 비트맵을 타겟으로 하는 DC가 필요하다.
	m_memDC = CreateCompatibleDC(m_hDc);

	// 그러나 만든 비트맵과 DC가 연결점이 존재하지 않기때문에 SelectObject를 사용한다. 
	// 비트맵을 전달하면 비트맵이 되돌아 나오게 되므로 이를 제거한다.
	// DC가 만들어지면 디폴트로 1픽셀짜리 비트맵이 만들어진다.
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
	update();

	render();
}

// 물체들의 변경점을 체크하는 곳
void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
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
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	 
	
	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC,int(vPos.x - vScale.x / 2.f)
		           ,int(vPos.y - vScale.y / 2.f)
		           ,int(vPos.x + vScale.x / 2.f)
		           ,int(vPos.y + vScale.y / 2.f));

	// 복사 받을 DC , 범위 좌상단 x, y, 우하단, x, y, 복사할 DC, 좌상단 x ,y, SRCCOPY는 복사 명령어
	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
