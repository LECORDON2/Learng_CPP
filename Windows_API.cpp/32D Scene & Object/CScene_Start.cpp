#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"


CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	// 부모쪽의 멤버함수를 오버라이딩 하는 법
	// 이렇게 하는 이유는 update에서 더 구현하기 위해서이다.
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::Enter()
{

	// object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// 부모 포인터로 받았지만 실제객체는 CPlayer이기 때문에
	// CPlayer의 복사생성자에느 CPlayer를 넣어주어야 하므로 다운캐스팅을 하여 넣어준다.
	//CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// 몬스터 배치
	// 변수 선언과 동시에 = 은 복사행성자가 호출된다.
	int iMonCount = 2;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::Getinst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	float fTern = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);
	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster object 추가
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTern, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌 체크

	CCollisionMgr::Getinst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::Getinst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
}

void CScene_Start::Exit()
{
	DeleteAll();

	// Scene을 빠져나갈때 충동 관계 리셋
	CCollisionMgr::Getinst()->Reset();
}
