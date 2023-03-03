#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner; // Collider를 소유하고 있는 오브젝트

	// 충돌 판정의 유연성을 위해서 오프셋(기준으로 부터 상대적 거리 값)을 설정
	Vec2 m_vOffsetPos; // 오브젝트로 부터 상대적인 위치
	Vec2 m_vFinalPos;  // finalupdate 에서 매 프레임마다 계산
	Vec2 m_vScale;     // 충돌체의 크기

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void finalupdate();

	void render(HDC _dc);

	CCollider();
	~CCollider();

	friend class CObject;
};
