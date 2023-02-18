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
};
