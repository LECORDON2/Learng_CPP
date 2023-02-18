#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// object 추가
	CObject* pObj = new CObject;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
  
	// m_arrObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj); 
	
	// 그러나 이러한 방법은 어느정도 공개가 되는 것이므로 디버깅에 힘들수 있다.
	// 그러므로 멤버를 private로 만들도 protected 함수를 만드는 방법을 사용한다.
  // 부모 멤버에 접근하기 위해 부모 멤버 함수를 protected로 만든다.
	AddObject(pObj, GROUP_TYPE::DEFAULT);
}

void CScene_Start::Exit()
{
}
