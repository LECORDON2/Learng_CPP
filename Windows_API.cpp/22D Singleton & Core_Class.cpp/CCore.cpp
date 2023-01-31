#include "pch.h"
#include "CCore.h"

CCore::CCore()
{
}

CCore::~CCore()
{
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 크기 조정

	return S_OK;
}

void CCore::progress()
{

}

//int CCore::init()
//{
//	// Windows에서 제공하는 함수 대부문의 결과 값이 HRESULT(long)
//	//HRESULT hr = S_OK;
//
//	//if (FAILED(S_OK)) // 안에 있는 값이 음수면 true, E_FAIL = 음수
//	//{
//
//	//}
//	//E_FAIL;
//
//	return E_FAIL;
//
//	return S_OK; // S_OK = 0;
//}
