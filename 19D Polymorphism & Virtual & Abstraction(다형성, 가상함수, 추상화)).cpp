#include <iostream>

using std::cout;
using std::endl;

class CParent
{
// private:
//	 int   m_i;
protected:
	int   m_i;

public:
	void SetInt(int _a)
	{
		m_i = _a;
	}
	
	virtual void output()  // virtual은 가상함수
	{
		cout << "Parent" << endl;
	}

public:
	CParent()
		: m_i(0)
	{
		cout << "부모 생성자" << endl;
	}
	
	CParent(int _a)
		: m_i(_a)
	{
		cout << "부모 생성자" << endl;
	}
	
	~CParent()
	{
		cout << "부모 소멸자" << endl;
	}
};


class CChild : public CParent
{
private:
	float m_f;

public:
	void SetFloat(float _f)
	{
		m_f = _f;
		m_i = 100; 
	}
  
	void output()
	{
		cout << "Child" << endl;
	}

public:
	CChild()
		: CParent()  
		, m_f(0.f)   
	{
		
		cout << "자식 생성자" << endl;
	}
	~CChild()
	{
		cout << "자식 소멸자" << endl;
	}
};

int main()
{
	// 객체지향 언어 특징
	// 1. 캡슐화 (은닉성)
	// 2. 상속
	// 3. 다형성
	// 4. 추상화


	// 다형성

	// 상속 and 포인터
	// 상속 될때 parent가 먼저 메모리에 잡힌다.
	CParent parent;
	CChild child;

	// CParent* pParent = &parent; // 문제 없음
	// CChild* pChild = &child;     // 문제 없음

	// CParent* pParrent = &child;  // 문제 없음(먼저 잡힌 parent 객체를 보기에)
	// CChild* pChild = &parent;    // 문제 있음
	
	// parent의 자식이 있고 그 자식들에게 또 자식이 있어도 메모리의 맨 앞에는 parent가 있으므로 parent*로 가리킬 수 있다.

	// pParent; // 이것으로 많은 객체들을 가리킬 수 있지만 실제 객체가 뭔지는 알기 힘들다.

	CParent* pParent = nullptr;

	parent.output();
	pParent = &parent;
	pParent->output();

	child.output();
	pParent = &child;
	pParent->output(); // parent가 출력된다. // virtual(가상 함수)를 쓴다면 child가 나옴

	((CChild*)pParent)->NewFunc(); // 얀간더 위험한 방법

	CChild* pChild = dynamic_cast<CChild*>(pParent);
	if (nullptr != pChild)
	{
		pChild->NewFunc();
	}

	// 다형성, 가상함수(virtual)
	// 부모 포인터 타입으로, 부모 클래스로부터 파생되는 자식클래스 객체들의 주소를 가리킬 수 있다.
	// 모든 객체를 부모 클래스 타입으로 인식하게 되기 때문에, 실제 객체가 무엇인지 알 수 없다.
	// virtual 키워드를 통해서, 각 클래스는 자신만의 고유한 가상함수 테이블을 가지게 된다.
	// 각 클래스의 객체들은 가상함수 테이블 포잍너에서 해당 클래스에 맞는 테이블을 가리키게 된다.
	// 그 테이블에는 해당 클래스의 가상함수들이 등록

	// 다운 캐스팅
	// 부모 클래스에서 선언되지 않은, 오직 자식쪽에서만 추가된 함수를 호출하고 싶을 때
	// 자식 포인터타입으로 일시적으로 캐스팅해서 호출한다.
	// 문제가 발생 할 수 있기 때문에 dynamic_cast로 안전하게 확인해 볼 수 있다.
	// RTTI(Run Time Type Identification or information)

	// 추상화
	// 실체 객체를 생성할 목적의 클래스가 아닌, 상속을 통해서 구현해야할 내용을 전달하는 상속 목적으로 만들어진 크랠스
	// virtual , = 0(1개 이상의 순수가상함수를 포함하면 추상클래스가 된다.)

	return 0;
}
