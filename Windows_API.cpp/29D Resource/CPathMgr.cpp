#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}

CPathMgr::~CPathMgr()
{}

void CPathMgr::init()
{
	// 현재 디렉토리를 기억하는 윈도우 함수
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = wcslen(m_szContentPath);

	// 상위폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// content폴더로 가기위해 문자열 이어 붙이기
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	// + bin\\content\\
	// 그냥 GetCurrentDirectory(255, m_szContentPath); 를 쓸 
	// 프로젝트 경로가 나오게 된다.
	// 속성 -> 디버깅 에서 작업 디렉토리를 바꾸어 주면 된다.
	// SetWindowText(CCore::Getinst()->GetMainHwnd(), m_szContentPath);
}
