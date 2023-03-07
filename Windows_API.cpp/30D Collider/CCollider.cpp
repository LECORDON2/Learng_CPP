#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_vOffsetPos{}
	, m_vFinalPos{}
	, m_iID(g_iNextID++) // Collider가 생성될때 마다 ID값이 증가하면서 겹칠 수 없다.
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr) // _origin.m_pOwner라고 하면 origin의 오브젝트를 가리키게 되므로 nullptr
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++) // 새로운 ID 받아옴
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

	// 음수가 되는 경우 방어
	assert(0 <= m_iCol);
}

void CCollider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_iCol)
	{
		ePen = PEN_TYPE::RED;
	}

	// 변수명 없이 클래스를 생성하면 임시 객체로 지역변수로 만들어진다.
	// 임시 객체이기 때문에 바로 소멸이 되므로 이름이 필요하다
	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc 
		         , (int)(m_vFinalPos.x - m_vScale.x / 2.f)
	             , (int)(m_vFinalPos.y - m_vScale.y / 2.f)
	             , (int)(m_vFinalPos.x + m_vScale.x / 2.f)
	             , (int)(m_vFinalPos.y + m_vScale.y / 2.f));
}

void CCollider::OnCollision(CCollider* _pOther)
{
	
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	// 3개 이상의 개체가 있을 경우 감안
	++m_iCol;
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
}
