#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 갯수만큼 선언
	wstring          m_strName;                       // Scene 이름

public:
	void Setname(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void finalupdate();
	void render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene에 진입 시 호출
	virtual void Exit() = 0;  // 해당 Scene을 탈출 시 호출

	// 클래스는 헤더에 구현하면 inline처리 되어서 호출해도 해당스택에서 해결한다 고로 함수 호출비용이 없다.
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	// 임시객체가 아니라 원본을 받기위해 reference, 그리고 수정할 수 없게 하기위해 const
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	
public:
	CScene();
	virtual ~CScene();
};
