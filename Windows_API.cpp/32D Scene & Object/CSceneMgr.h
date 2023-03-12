#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // 모든 씬 목록
	CScene* m_pCurScene;                       // 현재 씬

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	// 업데이트 도중이나 렌더되기 전 같이 중간에 Scene이 바뀌어 버리면 문제가 생길 수 있으므로 
	// EventMgr을 통해서 바꾼다.
	// 아무나 막 호출하면 안되기 때문에 private
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};
