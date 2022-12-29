#include <stdio.h>
#include <stdlib.h>


int main()
{

	

	// void *

	// 1. 원본의 자료형을 정하지 않음
	// 2. 어떠한 타입의 변수의 주소든 다 저장 가능
	// 3. 역참조 불가능 
	// 4. 주소 연산 불가능


	void* pVoid = nullptr;
	// 주소를 저장할 수 있는 변수는 맞지만, 주소로 같을 때 원본의 형태를 정하지 않는 것
	// 어떤 주소의 변수도 받을 수 있다.


	{
		int a = 0;
		float f = 0.f;
		double d = 0.;
		long long ll = 0;

		pVoid = &a;
		pVoid = &f;
		pVoid = &d;
		pVoid = &ll;
		// 이처럼 어떤 주소의 변수든 받을 수 있다.
		// 그렇기에 역참조가 불가능하다

		*pVoid;
		// 이러면 안된다.
		*pVoid + 1;
		// 주소 연산도 되지 않는다.

	}




	return 0;

}

