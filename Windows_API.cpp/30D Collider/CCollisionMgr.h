#pragma once

class CCollider;

//union Test // 4byte 사이즈 union은 제일 큰 사이즈 기준으로 같은 공간을 공유한다.
//{
//	// 같은 공간을 사용하지만 어떤 멤버로 지칭하는지에 따라서 바뀌게 된다.
//	int a;
//	float f;
//};

union COLLIDER_ID
{
	struct
	{
		UINT iLeft_id;
		UINT iRight_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	// 충돌체 간의 이전 프레임 충돌 정보
	map<ULONGLONG, bool> m_mapColInfo;

	// 32개의 그룹의 충돌 체크를 위해서 UINT를 사용(32 * 32 그림)
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 매트릭스


public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	// 내가 지정한 주소를 지정한 값으로 바이트 단위로 세팅하는 함수
	// 전부 0으로 만들기
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};
