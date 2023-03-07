#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	m_pTex = CResMgr::Getinst()->LoadTexture(L"PlaterTex", L"texture\\snake.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(25.f, 25.f));
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * FDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * FDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * FDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * FDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	// 입력 될 때는 음수가 될 수 있으므로 UINT -> int로 캐스팅
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	// 계산은 실수로 정확하게 하고 출력할 때는 정수로 전달한다.

	//BitBlt(_dc, (int)(vPos.x - (float)(iWidth / 2))
	//	, (int)(vPos.y - (float)(iHeight / 2))
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// 투명처리, 인자로 길이값도 요구(0, 0 이후) windows.h안에서 참조하고 있으므로 함수의 원형을 알고 있으나 실제 구현 부분은 없다.
	TransparentBlt(_dc, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
	    , RGB(255, 0 , 255)); // 투명 처리할 RGB값

	// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CScene* pCurscene = CSceneMgr::Getinst()->GetCurScene();
	pCurscene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

