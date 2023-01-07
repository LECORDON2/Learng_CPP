#include <stdio.h>
#include "Dynamic_Array.h"
#include <iostream>
#include <time.h> // 랜덤함수 참조

int main()
{
	// 난수(랜덤)
	srand(time(nullptr)); // 시드(시간 값)를 통해 난수 페이지 변경
	rand(); // 난수 페이지 참조
	// 0 ~ 100 사이의 난수는 100으로 나눈 나머지
	// 50 ~ 100 사이의 난수는 50의 나머지에 + 50

	DAryST s1 = {};
	InitDArry(&s1);

	for (int i = 0; i < 10; ++i)
	{
		int iRand = rand() % 100 + 1; // 1 ~ 100 까지의 난수
		PushBack(&s1, iRand);
	}
	for (int i = 0; i < s1.iCount; ++i)
	{
		printf("%d\n", s1.pInt[i]);
	}
	
	printf("정렬 전\n");

	Sort(&s1);

	printf("정렬 후\n");

	for (int i = 0; i < s1.iCount; ++i)
	{
		printf("%d\n", s1.pInt[i]);
	}


	ReleaseDA(&s1);



	// 내가 만든 정렬 
	DAryST MyArry = {};

	InitDArry(&MyArry);

	PushBack(&MyArry, 10);
	PushBack(&MyArry, 50);
	PushBack(&MyArry, 30);
	PushBack(&MyArry, 50);
	PushBack(&MyArry, 60);
	PushBack(&MyArry, 16);


	SortDA(&MyArry);

	int a = MyArry.pInt[0];
	int b = MyArry.pInt[1];
	int c = MyArry.pInt[2];
	int d = MyArry.pInt[3];
	int e = MyArry.pInt[4];
	int f = MyArry.pInt[5];


	ReleaseDA(&MyArry);
	

	// 버블, 선택, 합병, 삽입, 쾌속, 힙 정렬(완전 이진트리부터 공부) 구현해보기

	return 0;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dynamic_Array.h

#pragma once

typedef struct _tagDArray
{
	int* pInt;
	int iCount;
	int iMaxcount;

}DAryST;


void InitDArry(DAryST* _DArry);

void PushBack(DAryST* _DArry, int _iData);

// 내가 만든 정렬 함수
void SortDA(DAryST* _Darry);

// 선생님이 만든 데이터 정렬 함수
void Sort(DAryST* _DArry);

void ReleaseDA(DAryST* _DArry);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dynamic_Array.cpp

#include <iostream>
#include "Dynamic_Array.h"

void InitDArry(DAryST* _DArry)
{
	_DArry->pInt = (int*)malloc(sizeof(int) * 2);
	_DArry->iCount = 0;
	_DArry->iMaxcount = 2;
}

void Relocate(DAryST* _DArry)
{
	int* Newloc = (int*)malloc(_DArry->iMaxcount * sizeof(int) * 2);
	for (int i = 0; i < _DArry->iCount; ++i)
	{
		Newloc[i] = _DArry->pInt[i];
	}
	int* Free_Point = _DArry->pInt;
	_DArry->pInt = Newloc;
	free(Free_Point);
	_DArry->iMaxcount *= 2;
}

void PushBack(DAryST* _DArry, int _iData)
{
	if (_DArry->iCount < _DArry->iMaxcount)
	{
		_DArry->pInt[_DArry->iCount++] = _iData;
	}
	else
	{
		Relocate(_DArry);
		_DArry->pInt[_DArry->iCount++] = _iData;
	}
}

void SortDA(DAryST* _DArry)
{
	// iCount - 1번 만큼 반복해야 함
	for (int j = 0; j < _DArry->iCount - 1; ++j)
	{
		for (int i = 0; i < _DArry->iCount - 1; ++i) // 버블 정렬 사용(1 회전)
		{
			int S = 0;
			if (_DArry->pInt[i] > _DArry->pInt[i + 1])  // 구조체 포인터로 접근하여 구조체 내의 멤버인 힘 메모리 포인터로 접근한다.
			{
				S = _DArry->pInt[i];
				_DArry->pInt[i] = _DArry->pInt[i + 1];   // [0]과 [1] 비교 후 교환, [1]과 [2] 비교 후 교환, [2]과 [3] 비교 후 교환....
				_DArry->pInt[i + 1] = S;
			}
		}
	}
}

void Sort(DAryST* _DArry)
{
	if (_DArry->iCount <= 0) // 안에 있는 것이 없을 경우의 예외 처리
	{
		return;
	}
	while (true)
	{
		bool bFunish = true;
		int iLoop = _DArry->iCount - 1;
		for (int i = 0; i < iLoop; ++i)
		{
			if (_DArry->pInt[i] > _DArry->pInt[i + 1])
			{
				int iTemp = _DArry->pInt[i];
				_DArry->pInt[i] = _DArry->pInt[i + 1];
				_DArry->pInt[i + 1] = iTemp;
				bFunish = false;
			}
		}
		if (bFunish)        // 배열의 숫자 중 둘을 비교했을 때 하나라도 내림차순으로 되어 있다면 위의 if 문의 bFunish = false; 때문에 while문은 break 되지 않는다.
		{
			break;
		}
	}
}

void ReleaseDA(DAryST* _DArry)
{
	free(_DArry->pInt);
	_DArry->iCount = 0;
	_DArry->iMaxcount = 0;
}
