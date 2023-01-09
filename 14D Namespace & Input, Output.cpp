#include <iostream>
#include "Clist.h"

void MYEndL()
{
	wprintf(L"\n");   // \n 콘솔창에서 커서를 아래로 하나 내려가게 함
}

namespace MYSPACE
{
	int g_int;   // 전역 변수가 됨
}                // MYSPACE::g_int = 0;// main에선 이런식으로 접근해야 함

namespace OHTERSPACE
{
	int g_int;
}

// using namespace std;    // namespace를 없이 쓸 수 있게 만들어 준다.

using std::cout;
using std::endl;           // 특정 기능만 namespace쓰지 않게 할 수 있다. 

class CTest
{
private:
	int m_i;

	// 객체 업이 호출 가능
	static void MemberFunc() // CTest::MemberFunc(); 이런식으로 가능하다.
	{
		
	}
};

class CMyOstream
{
public:
	CMyOstream& operator << (int _idata)
	{
		printf("%d", _idata);
		return *this;
	}
	
	CMyOstream& operator << (const wchar_t* _pString)
	{
		wprintf(L"%s", _pString);
		return *this;
	}

	CMyOstream& operator << (int& _idata)
	{
		scanf_s("%d", _idata);
		return *this;
	}

	CMyOstream& operator << (void(*_pFunc)(void))
	{
		_pFunc();
		return *this;
	}

};

CMyOstream mycout; // 안에 아무것도 없는 클래스면 1byte를 준다.

int main()
{


	// C printf 대체
	std::cout << "안녕" << 10 << std::endl;   // << 은 연산자 오버로딩, 자기자신을 호출하여 연속으로 연산 가능

	// C scanf 대체
	int iInput = 0;
	std::cin >> iInput;




	MYSPACE::g_int = 0;        // 이런식으로 접근해야 함
	OHTERSPACE::g_int = 0;     // 변수명이 같아도 이런식으로 접근이 가능하다.


	mycout << 10; // 이러면 연산자가 호출됨


	mycout << 10 << L"" << MYEndL;
	
	CTest::MemberFunc();

	return 0;

}
