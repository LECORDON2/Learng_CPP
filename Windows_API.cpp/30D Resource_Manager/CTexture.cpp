#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{ 
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	// BITMAP 데이터 형태로 로딩, size 0, 0 이면 default 값, LR_CREATEDIBSECTION | LR_LOADFROMFILE는 로드 옵션
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// 비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(CCore::Getinst()->GetMainDC());

	// 비트맴과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo); // 특정 오브젝트의 정보를 알려주는 함수
}
