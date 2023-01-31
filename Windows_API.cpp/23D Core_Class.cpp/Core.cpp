#include "pch.h"
#include "CCore.h"
#include "CObject.h"

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

	// 해상도에 맞게 크기 조정
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};

	// RECT 포인터, 스타일 정보(WS_OVERLAPPED은 자주쓰는 것을 묶어서 비트값을 합쳐 놓은 것), 메뉴바감안 해서 계산
	// 함수를 통해서 계산을 하여 값을 확인하고 주소를 통해서 값을 rt에 되돌려 받는다. _Inout_ 뜻
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // 계산 결과 {-8, -51, 1288, 776}

	// x, y 전체 화면 기준 어디 픽셀인지에 대한 것, cx,cy가 가로세로
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// 윈도우가 제공하는 메세지 기반이 아닌 GetDC, Curnel object라 지워야 한다.
	m_hDc = GetDC(m_hWnd);   

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{100, 100};

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

	update();
	render();
}

// 물체들의 변경점을 체크하는 곳
void CCore::update()
{
	// 포커스 안되어 있을 때도 입력 될 수 있으니 조심
	// 되돌려준 값에서 지금 이순간에 눌렸는지만 체크하고 싶으면 제일 상위 비트를 확인하면 된다.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// 그리기
	Rectangle(m_hDc, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		           , g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		           , g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		           , g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
