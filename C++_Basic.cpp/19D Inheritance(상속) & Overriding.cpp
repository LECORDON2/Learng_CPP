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
	
	void output()
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

// 상속
// 상속을 받는 다는 것은 상속한 클래스의 기능을 가져오는 것
// 코드의 재사용성을 올리기 위함
class CChild : public CParent
{
private:
	float m_f;

public:
	void SetFloat(float _f)
	{
		m_f = _f;
		// this->m_i = 100; // 이것은 문제가 된다. 부모쪽 private는 접근이 안된다.
		// private를 public으로 바꾸면 되지만 이러면 완전히 외부에도 공개가 된다.
		// 그럴 때 쓰는 접근 지정자가 protected
		m_i = 100; 
	}
	// 상속받은 부모 클래스의 함수를 재정의(오버라이딩) 함
	void output()
	{
		cout << "Child" << endl;
	}

public:
	CChild()
		: CParent()  // 생성자 함수를 호출하는 코드가 생략이 되어 있는 것. 그래서 m_f(0.f) 실행되기전 CParent()가 실행 되는 것. 
		, m_f(0.f)   // 호출은 child가 빠르다. 초기화는 parent가 빠르다.
		
    // : m_f(0.f)  이렇게 거꾸로 적어도 parent가 더 빠르다.
		// , CParent() 
    
		// , m_i(0) 이것은 안된다. 초기화는 반드시 각자 자기쪽에서 해주어야 한다. initialized
		// , CParent(1000) 부모쪽 생성자가 오버로딩 되어있는 경우 자식쪽에서 따로 표시를 해주지 않으면 기본 생성자가 호출된다.
	{
		// m_i = 0; 이것은 된다. 부모 쪽 멤버에 접근해서 0넣은 것이기 때문(protected)
		cout << "자식 생성자" << endl;
	}
	~CChild()
	{
		cout << "자식 소멸자" << endl;
		// 상속받은 부모의 소멸자를 호출하는 코드가 보이지는 않지만 존재한다.
		// 소멸자는 자식이 먼저 호출, 실행되고 부모로 올라간다.
	}
};

// 해당 클래스에서 해결할 일은 각자의 멤버함수로 해결하기, parent 파트의 m_i를 child의 생성자에 넣으면 안된다.

class CChildCChild : public CChild   // 이 클래스의 객체를 만들면 parent, CChild, CChildCChild 순서로 메모리가 잡힌다.
{
private:
	long long m_ll;
};


void FuncA()
{
	cout << "FuncA" << endl;
}

void FuncB()
{
	FuncA();
	cout << "FuncB" << endl;
}


int main()
{
	// 객체지향 언어 특징
	// 1. 캡슐화 (은닉성)
	// 2. 상속
	// 3. 다형성
	// 4. 추상화

	CParent parent;  // 4byte 크기
	CChild child;    // 8byte 크기, 메모리 상에서 Parent 파트와 chlid 파트가 있다.

	parent.SetInt(10); // 문제가 없음
	child.SetInt(10);  // child 객체안 parent 파트의 m_i에 값을 넣어주겠다는 뜻

	CChild child; // 생성자 호출 순서는 child 다음 parent이다. 객체의 주체가 child이기 때문이다.

	FuncB(); 
	// 할 경우 A->B 순서로 나온다. 호출순서는 B가 먼저이지만 실행 순서는 A가 먼저이다.
	// FuncA()가 먼저 완료 되어서 cout << "FuncA" << endl;가 실행

	// 상속
	// 자식 or 부모 클래스는 상속관계에서 다른 클래스의 멤버를 초기화 할 수 없다.(초기화 한정)
	// 생성자 호출 순서 자식 -> 부모
	// 생성자 실행 순서, 초기화 순서 부모 -> 자식

	// 소멸자 실행 및 호출 순서, 자식 -> 부모
	
	// 오버 라이딩
	// 부모 클래스의 멤버함수를 자식쪽에서 재정의 함으로써, 자식 클래스에 구현된 기능이 호출되도록 한다.
	parent.output();
	child.output(); // 자식에게 같은 함수가 없다면 상속 받았기에 부모쪽 함수를 사용할 수 있음
	                // 그러나 자식쪽에서 똑같은 함수가 있다면 자식쪽 함수를 사용한다. 덮어쓴 것(오버라이딩)
	child.CParent::output(); // 이런식으로 부모 쪽 함수를 호출 할 수도 있다.


	return 0;
}
