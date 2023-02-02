include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,  //LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP,    //UP,
	VK_DOWN,  //DOWN,
	'Q',      //Q,
	'W',      //W,
	'E',      //E,
	'R',      //R,
	'T',      //T,
	'Y',      //Y,
	'U',      //U,
	'I',      //I,
	'O',      //O,
	'P',      //P,
	'A',      //A,
	'S',      //S,
	'D',      //D,
	'F',      //F,
	'G',      //G,
	'Z',      //Z,
	'X',      //X,
	'C',      //C,
	'V',      //V,
	'B',      //B,
	VK_MENU,          //ALT,
	VK_CONTROL,       //CTRL,
	VK_LSHIFT,        //LSHIFT,
	VK_SPACE,         //SPACE,
	VK_RETURN,        //ENTER,
	VK_ESCAPE,         //ESC,
	//
	//LAST,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}


void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

	// m_vecKey[(int)KEY::LEFT]; // (int)KEY::LEFT 는 0
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아보기

	// 메인 윈도우가 포커스 되어있을때 CkeyMgr가 작동되게 하려면 사용한다.
	HWND hMainWnd = CCore::Getinst()->GetMainHwnd();

	// 현재 포커스 되어있는 윈도우의 핸들 값을 알려줌, 포커스 되어있는 것이 없다면  nullptr
	// 프로그램이 보유하고 있는 모든 윈도우중 하나만이라도 포커스 되어있을때 CkeyMgr이 동작하게 만들려면 nullptr인지만 체크하면 된다.
	HWND hWnd = GetFocus(); 
	
	// 윈도우 포커싱 중일 때 키 이벤트 동작
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//  키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려 있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}

			// 키가 안눌려있다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에는 눌렸다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 안눌려있었다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
	}

	// 윈도우 포커싱 해제상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState) // AWAY된 키들도 다음 프레임에 NONE이 된다.
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
