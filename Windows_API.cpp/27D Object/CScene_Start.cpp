#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

	// 몬스터 배치
	// 변수 선언과 동시에 = 은 복사행성자가 호출된다.
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::Getinst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	float fTern = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)iMonCount - 1;
	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster object 추가
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTern, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{
}
