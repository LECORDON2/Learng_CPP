#include <iostream>
#include "Arr.h"







int main()
{


	// 가변배열
	//int a = 100;
	//scanf_s("%d", &a);

	// int arr[a] = {};
	// a는 변수다. main함수는 미리 메모리의 영역을 정해놓기 때문에 해제도 하는데
	// 변수의 값을 확신할 수 없으면 안된다. 지역변수로 가변배열은 불가능하다.
	// 가변배열을 만들기 위해선 동적 할당을 사용할 수 밖에 없다.

	// 배열 개수를 선언할 때에는 변수를 사용 할 수 없다.

	// 객체(Instance)
	// int는 자료형
	// int a; a는 객체
	// 의도한 자료형의 실질적인 데이터


	tArr s = {};
	InitArr(&s);

	for (int i = 0; i < 10, ++i)
	{
		PushBack(&s, i);

	}
	
	// 배열 객체는 main함수가 끝날때 해제됨
	// 힙 메모리 해제도 해줘야함
	ReleaseArr(&s);

	// tArr s = {};
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
	_pArr->pInt[_pArr->iCount++] = _iData; // (*_pArr).pInt[(*_pArr).iCount++] = _iData
}

// 공간 추가 확장
void Reallocate(tArr* _pArr)
{
	// 1. 2배 더큰 공간을 동적 할당 한다. 
	int* pNew = (int*)malloc(_pArr->iMaxcount * 2 * sizeof(int)); // (*_pArr).iMaxcount * sizeof(int) * 2

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
	free(_pArr->pInt);  // (*_pArr).pInt
	_pArr->iCount = 0;
	_pArr->iMaxcount = 0;

}

