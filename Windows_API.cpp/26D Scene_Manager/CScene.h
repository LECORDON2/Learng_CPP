#pragma once

class CObject;
// 전방 선얼을 할 경우 클래스 타입 자체는 쓸 수 없다. 구체적인 정보가 없고 나중에 링크로 넘기는 것이기 때문에
// 포인터 사이즈는 고정되어 있으므로 포인터는 가능하다. 
// 전방 선언을 하는 이유는 컴파일 속도에 영향을 주지 않기 위해서이다.
// 직접 헤더를 참조했다면 CObject가 변경 되었을때 CScene 쪽 코드도 매번 확인을 해야하기 때문이다.
// 하지만 CScene는 CObject를 정확히 알지는 못하고 있다는 것만을 알기 때문에 CObject가 변경되도 CScene은 대응할 필요가 없다.
// 헤더가 헤더를 참조하는 것을 방지하고자 전방선언을 사용

// 상속을 시킬 목적의 클래스, 소멸자의 가상함수화 필수
class CScene
{
private:
	// CObject는 앞으로 파생될 모든 Object의 부모타입이므로 자식들의 포인터를 받을 수 있으므로 CObject*를 사용
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 갯수만큼 선언
	wstring          m_strName;                       // Scene 이름

public:
	void Setname(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// 모든 Scene이 Start라는 함수를 가질 것이며 부모 클래스 포인터로 가리켜도 자식이 가지는 함수를 호출하기 위해 virtual로 만듬
	// 그래서 구현할 필요가 없다.
	// 이는 순수 가상함수이며 함수 뒤에 = 0 을 붙인다. 또한 이렇게 선언된 순수 가상함수가 있다면 이를 추상클래스라고 하며
	// 추상클래스는 객체를 만들지 못하고 상속으로서만 사용된다.
	// 그리고 추상클래스를 상속받은 자식클래스는 무조건 해당 순수 가상함수를 override 시켜줘야한다.
	// 순수 가상함수를 통해서 2가지 효과를 얻을 수 있다.
	// CScene을 상속밭은 클래스가 Enter를 구현하지 않으면 정상적으로 객체화 될 수 없다(강제화).
	// 부모 클래스인 CScene은 객체를 만들수 없다.
	virtual void Enter() = 0; // 해당 Scene에 진입 시 호출
	virtual void Exit() = 0;  // 해당 Scene을 탈출 시 호출

	// 클래스는 헤더에 구현하면 inline처리 되어서 호출해도 해당스택에서 해결한다 고로 함수 호출비용이 없다.
protected:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	
public:
	CScene();
	
	// CScene의 자식 class는 CScene을 부모 class로 사용하고 CSceneMgr 또한 
	// CScene 타입을 사용하기 때문에 이를 지우기 위해 delete한다면 부모쪽의 소멸자만 호출되게 된다.
	// 그래서 virtual을 사용하여 자식쪽의 소멸자를 호출한다.
	// 이는 대부분 상속에 해당한다.
	virtual ~CScene();
	
};
