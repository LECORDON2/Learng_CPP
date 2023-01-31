#include <stdio.h>

// 구조체
// 사용자 정의 자료형 : 기본적으로 제공하는 자료형 말고 내 코드에서만 적용될 내가 직접 만든 자료형
// 자료형 : 데이터가 어떤 형태인지 설명해주는 datertype



typedef struct _tagMyST
{
	int a;
	float f;
	// 변수가 선언된 것이 아니라, 자료형 내부가 이렇게 구성되어 있을것이라는것 설명

}MYST;


// 원래 C언어 에서는 struct _tagMyST롤 쓰면서 struct를 붙여야 되는데
// 이를 MYST로 이름을 통채로 준것
// C++은 struct를 붙일 필요는 없다.


typedef struct _tagBig
{
	MYST k;
	int i;
	char c;

}BIG;

// 기본 자료형으로 만든 것으로 다른 구조체의 일부로 삼아 확장 되는 것

typedef int INT;

// typedef는 타입을 재정의 -> INT를 곧 int로 받아들임



int main()
{




	// 구조체


	MYST t = {100, 3.14f};
	// int 자리에는 100을 넣고 실수 자리에는 3.14f를 넣어라


	int iSize = sizeof(MYST); // 자료형이 의미하는 사이즈가 얼마인지 알려줌
	// int 자료형 하나랑 float 자료형 하나가 묶여서 생성된 8btye 짜리 

	t.a = 10;
	t.f = 10.215f;


	return 0;

}



