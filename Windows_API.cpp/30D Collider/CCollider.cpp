#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_vOffsetPos{}
	, m_vFinalPos{}
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// Object의 위치를 따라 간다.

	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	// 변수명 없이 클래스를 생성하면 임시 객체로 지역변수로 만들어진다.
	// 임시 객체이기 때문에 바로 소멸이 되므로 이름이 필요하다
	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc 
		         , (int)(m_vFinalPos.x - m_vScale.x / 2.f)
	             , (int)(m_vFinalPos.y - m_vScale.y / 2.f)
	             , (int)(m_vFinalPos.x + m_vScale.x / 2.f)
	             , (int)(m_vFinalPos.y + m_vScale.y / 2.f));
}				  
