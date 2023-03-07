#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; // Collider를 소유하고 있는 오브젝트

	// 충돌 판정의 유연성을 위해서 오프셋(기준으로 부터 상대적 거리 값)을 설정
	Vec2 m_vOffsetPos; // 오브젝트로 부터 상대적인 위치
	Vec2 m_vFinalPos;  // finalupdate 에서 매 프레임마다 계산
	Vec2 m_vScale;     // 충돌체의 크기

	UINT m_iID;        // 충돌체 고유한 ID 값
	UINT m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }
	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther); // 충돌 집입 시
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제 시

	CCollider& operator = (CCollider& _origin) = delete; // 디폴트 대입연사자를 방어하기 위해서 대입 오퍼레이트 함수 삭제

public:
	CCollider();
	CCollider(const CCollider& _origin); // 복사된 객체도 고유한 ID를 가지고 있어야 하므로 복사생성자를 따로 만든다.(deep copy / 깊은 복사)
	~CCollider();

	friend class CObject;
};
