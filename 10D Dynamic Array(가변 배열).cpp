#include <iostream>
#include "Arr.h"



// 변수
// 지역(스택)
// 전역, 정적, 외부(데이터)

// 메모리 영역
// 스택
// 데이터
// ROM
// 힘 영역(동적 할당)

// 프로그램 실행도중 원하는 만큼 메모리를 요청하는 것이 동적 할당

int g_i = 100;

typedef struct _tagST
{
	int iArr[10];
	// int iArr[g_i]; 이것도 안된다. 

}ST;
// 구조체 안에 배열도 들어감



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



	// 가변배열
	//int a = 100;

	//scanf_s("%d", &a);

	// int arr[a] = {};
	// a는 변수다. main함수는 미리 메모리의 영역을 정해놓기 때문에 해제도 하는데
	// 변수의 값을 확신할 수 없으면 안된다. 지역변수로 가변배열은 불가능하다.
	// 가변배열을 만들기 위해선 동적 할당을 사용할 수 밖에 업삳.

	// 배열 개수를 선언할 때에는 변수를 사용 할 수 없다.

	// 객체(Instance)
	// int는 자료형
	// int a; a는 객체
	// 의도한 자료형의 실질적인 데이터



	tArr arr;
	tArr arr2;



	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	tArr s = {};
	InitArr(&s);


	for (int i = 0; i < 10, ++i)
	{
		PushBack(&s, i);

	}



	// 배열 객체는 main함수가 끝날때 해제됨
	// 힙 메모리 해제도 해줘야함
	ReleaseArr(&s);


	// s; // 힙 메모리에 저장함, 스스로의 메모리의 한계 때문에
	// s.pInt = (int*)malloc(40); // 시작 주소를 알려줘야함
	// s.iCount = 0;
	// s.iMaxcount = 10;
	// 매번 하기 불편하니 함수로 만들기

	Reallocate(&s);
	// 헤더에 있기 때문에 main에서도 호출 할 수 있다.
	// 그게 싫으면 헤더 파일에 명시하지 않아도 됨


	

	return 0;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Arr.h
#pragma once


typedef struct _tabArr
{
	int* pInt;
	int iCount;
	int iMaxcount;
}tArr;


// 단축키 Ctrl + '+', '.' 
// 배열 초기화 함수
void InitArr(tArr* _pArr);

// 데이터 추가 함수
void PushBack(tArr* _pArr, int _iData);

// 공간 추가 확장, 이 부분이 main에서 독립적으로 호출되는 것이 싫으면 지워도됨, Arr.cpp에 있기 때문
void Reallocate(tArr* _pArr);

// 배열 메모리 해제 함수
void ReleaseArr(tArr* _pArr);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Arr.h"

#include <iostream>

void InitArr(tArr* _pArr)
{
	_pArr->pInt = (int*)malloc(sizeof(int) * 2); 
	_pArr->iCount = 0;
	_pArr->iMaxcount = 2;
}

void PushBack(tArr* _pArr, int _iData)
{
	// 힙 영역에 할당한 공간이 다 참
	if (_pArr->iMaxcount <= _pArr->iCount)
	{
		// 재할당
		Reallocate(_pArr);
	}
	// 데이터 추가
	_pArr->pInt[_pArr->iCount++] = _iData;
}

// 공간 추가 확장
void Reallocate(tArr* _pArr)
{
	// 1. 2배 더큰 공간을 동적 할당 한다. 
	int* pNew = (int*)malloc(_pArr->iMaxcount * 2 * sizeof(int));

	// 2. 기존 공간에 있던 데이터들을 새로 할당한 공간으로 복사시킨다.
	for (int i = 0; i < _pArr->iCount; ++i)
	{
		pNew[i] = _pArr->pInt[i];
	}

	// 3. 기존 공간은 메묄 해제
	free(_pArr->pInt);

	// 4. 배열이 새로 할당된 공간을 가리키게 한다.
	_pArr->pInt = pNew;

	// 5. Maxcount 변경점 적용
	_pArr->iMaxcount *= 2;
}

void ReleaseArr(tArr* _pArr)
{
	free(_pArr->pInt);
	_pArr->iCount = 0;
	_pArr->iMaxcount = 0;

}

