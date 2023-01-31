#include <iostream>
#include "LinkedList.h"

void Test()
{

}

int main()
{
  
  
	// 함수 포인터
	void(*pFunc)(void) = nullptr;
	// 반환타임이 void이고 인자도 아무것도 받지않는 함수의 주소를 받겠다.
	// pFunc이 그런 함수의 주소를 받는 포인트 변수
	pFunc = Test;
	pFunc();
	// Test함수를 호출하겠다는 것
	// 어떤 기능을 만들었고 그 기능을 사람들에게 줄 때 
	// 만약 다른 사람이 내 함수 다음에 다른 기능을 쓰고 싶을 때 call back을 만들어
	// 나중에 함수를 받는 경우를 위해서 함수 포인터를 사용한다.
	// 분기를 만들때

	return 0;
}
