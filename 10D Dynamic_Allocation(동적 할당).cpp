#include <iostream>

// 변수
// 지역(스택)
// 전역, 정적, 외부(데이터)

// 메모리 영역
// 스택
// 데이터
// ROM
// 힘 영역(동적 할당)

// 프로그램 실행도중 원하는 만큼 메모리를 요청하는 것이 동적 할당


int main()
{
	// malloc();
	// 내가 지정한 사이즈 만큼 힙영역에 메모리를 만듦 byte 단위
	// 메인함수가 시작되는 순간에 만들고 그 주소를 줌
	// 주소를 받은 애가 포인터 변수이다.

	int* pInt = (int*)malloc(100);


	// void pointer로 준다.
	// 내가 원하는 만큼 메모리를 잡을 수 있다.
	malloc(4);
	// 4byte 할당하고 시작 주소를 알려줌
	float* pF = (float*)malloc(4);

	*pF = 1.23f;
	// float포인터로 역참조를 하면 그곳을 float로 보는 것이다.
	
	// 동적할당을 요청 받은 malloc은 그 공간이 어떤 용도로 사용될 지는 사용자가 정하므로
	// void pointer로 준다.


	int* pI = (int*)pF;
	// int포인터로도 가리키고 float포인터로도 가리킴
	*pF = 2.4f;
	int i = *pI;
	// 실수 표현방식으로 저장도니 값을 정수 표현 방식으로 읽으면 이상해짐

	// 동적 할당
	// 1. 런타임 중에 대응 가능
	// 2. 사용자가 직접 관리해야함(해제)


	int iInput = 0;
	scanf_s(% d, &iInput);

	int* pInt = nullptr;
	if (100 == iInput)
	{
		pInt = (int*)malloc(100);

	}

	if (nullptr != pInt)
	{
		free(pInt); // free는 주소를 전달하면 주소가 가리키는 힙 메모리를 해제시켜 주는 함수
	}

	// 해제시켜주지 않으면 메모리 누수가 발생함



	return 0;

}
