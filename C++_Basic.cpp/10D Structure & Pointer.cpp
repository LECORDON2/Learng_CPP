#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>

typedef struct _tagMyST
{
	int a;  // 멤버 a랑 f는 변수가 아님
	float f;

}MYST;


int main()
{


	// 구조체와 포인터
	MYST s = {};
	s.a; // a파트를 지징하는 것

	MYST s2 = {};
	MYST s3 = {};

	s2.a;
	s3.a;


	MYST* pST = &s;
	// 주소에 갓을때
	pST + 1; // 8byte 씩 증가, 크기가 8byte이기 때문에

	(*pST).a = 100;
	(*pST).f = 1.121f;
	
	// 위와 똑같은 말
	pST->a = 100;
	pST->f =  3.14f;


	return 0;
}

