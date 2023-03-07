#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 행은 0부터 31까지, 열은 31부터 0까지 이므로
	// 행과 열이 같아지는 좌하-우상 대각선의 왼쪽(행이 열보다 작은 쪽)을 쓰기 때문에 
	// 더 작은 값의 그룹타입을 행으로,
	// 큰 값을 열(비트)로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		// 비트를 iCol만큼 비트 쉬프트
		m_arrCheck[iRow] |= (1 << iCol);
	}

}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// 검사하는 행의 비트 갯수가 하나씩 줄기 때문에 iRow부터 시작
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::Getinst()->GetCurScene();


	//vector<CObject*> vecLeft = pCurScene->GetGroupObject(_eLeft);
	//vector<CObject*> vecRight = pCurScene->GetGroupObject(_eRight);

	// 위처럼 하면 지역변수로 받는 것이기 때문에, 원본을 참조 받기위해서는 받은 때에도 const reference로 받아야한다.
	// 이렇게 해야 vecLeft, vecRight가 Scene에서 보유하고 있는 벡터로 볼 수 있다.
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider())
		{
			// 충돌체를 보유하지 않는 경우
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
			{
				// 충돌체가 없거나, 자기 자신과 충돌인 경우
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			// 각각의 ID로 채우면 두 충돌체의 고유한 값이 나온다.
			// 그 값을 키 값으로 사용하여 찾기
			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록('충동하지 않았다'로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중이다.
				if (iter->second)
				{
					// 이전에도 충돌하고 있었다.
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else
				{
					// 이전에는 충돌하지 않았다.
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;

				}
			}
			else
			{
				// 현재 충돌하고 있지 않다.
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRifghtPos = _pRightCol->GetFinalPos();
	Vec2 vRifhgtScale = _pRightCol->GetScale();

	if (abs(vRifghtPos.x - vLeftPos.x) < (vLeftScale.x + vRifhgtScale.x) / 2.f
		&& abs(vRifghtPos.y - vLeftPos.y) < (vLeftScale.y + vRifhgtScale.y) / 2.f)
	{
		return true;
	}
	

	return false;
}
