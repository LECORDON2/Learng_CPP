#include <iostream>
#include "Arr.h"
#include "CArr.h"

class CTest
{
private:
	int a;
public:
	CTest()
		: a(10)
	{
	}
};

int main()
{
	// 구조체 --> 클래스
	
	// 객체지향 언어 특징
	// 1. 캡슐화
	// 기능을 수행하기 위해 필요한 멤버 선언, 묶음, 은닉성
	// 멤버 함수들

	// 2. 상속

	// 3. 다형성

	// 4. 추상화

	// 구조체 버전 가변배열 --> 클래스 버전

	// C++ 동적할당 new, delete
	// 

	// 내부적으로 siezof 4 해서 malloc 동적할당을 하고
	// CTest 객체가 들어올 것이기에 생성자를 통해 초기화 까지 하고 주소를 준다.
	CTest* pTest = new CTest;  
	// pTest라는 객체를 가리키는 포인터라는 것을 토대로
	delete pTest; // 지워질 곳이 어떤 용도였던것인지 알려준다.

	// 구조체 예시

	tArr arr = {};
	InitArr(&arr);

	PushBack(&arr, 10);
	PushBack(&arr, 20);
	PushBack(&arr, 30);
	PushBack(&arr, 40);


	// CArr 예시
	
	CArr carr; // 이미 생성자가 호출됨 위의 InitiArr 까지와 같음

	carr.push_back(10);
	carr.push_back(20);
	carr.push_back(30);


	// int CArr::operator[](int idx)
	// {
	// 	 return m_pInt[idx];
	// }
	// operator 함수가 이러할 경우
	carr[1];  // operator 함수로 가능함
	

	 carr[1] = 400;  
  // 그러나 이건 안됨, 함수의 return 값은 임시공간안에 복사되어 저장되었다가 꺼내오는 것이므로
	// 밑의 식은 임시공간의 복사본을 수정하는 의미이므로 안된다. 원본이 수정되지도 않고 맞지도 않다.
	// 그러니 원본을 수정하고 싶으면 주소를 가져와야 한다.
	

	// int* CArr::operator[](int idx)
	// {
	//	 return m_pInt + idx;
	// }
	// 이렇게 하면 주소를 받아오는 것
	// 그러나 배열의 모양과는 다르다

	int* p = carr[1];
	*carr[1] = 100;

	// int& CArr::operator[](int idx)
	// {
	//	 return m_pInt[idx];
	// }
	// 이렇게 하면

	int iData = carr[1];  
	carr[1] = 100;
	// 가능하다.


	// 소멸은 신경쓰지 않아도 main안의 지역변수 carr을 지우기 위해서 소멸자가 호출될 것임


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CArr.h

#pragma once
class CArr
{
private:                 // 아무것도 안 적혀있다면 기본적으로 private
	int* m_pInt;
	int m_iCount;
	int m_iMaxCount;

public:
	void push_back(int _iData);
	void resize(int _iResizeCount);

	int& operator[] (int idx);

public:                  // 생성자를 private로 만들면 호출할 수 없어서 오류가 난다.
	CArr();
	~CArr();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CArr.cpp

#include "CArr.h"
#include <assert.h>


// class 밖에서 구현을 하게 된다면                
// ::는 CArr 안에 선언되어 있는 생성자 CArr 이라는 뜻, 범위를 지정해야함
CArr::CArr()
	: m_pInt(nullptr)
	, m_iCount(0)
	, m_iMaxCount(2)
{
	m_pInt = new int[2];           // C++ 스타일의 동적 할당
}

CArr::~CArr()
{                                  // int* p = new int; 일때는 delete p;로 쓰면 되지만
	delete[] m_pInt;                 // 단위가 연속되는 묶으르(배열형태) 있을때는 delete[]로 쓴다.
}

void CArr::push_back(int _iData)
{
	// 힙 영역에 할당한 공간이 다 참
	if (m_iMaxCount <= m_iCount) // (this->m_iMaxCount <= this->m_iCount)에서 this 생략
	{
		// 재할당
		resize(m_iMaxCount * 2);
	}
	// 데이터 추가
	m_pInt[m_iCount++] = _iData;  // this 생략
}

void CArr::resize(int _iResizeCount)
{
	// 현재 최대 수용량 보다 더 적은 수치로 확장하려는 경우
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);
	}

	// 1. 리사이즈 시킬 개수만큼 동적 할당 한다.
	int* pNew = new int[_iResizeCount];

	// 2. 기존 공간에 있던 데이터들을 새로 할당한 공간으로 복사시킨다.
	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_pInt[i];
	}

	// 3. 기존 공간은 메모리 해제
	delete[] m_pInt;

	// 4. 배열이 새로 할당된 공간을 가리키게 한다.
	m_pInt = pNew;

	// 5. iMaxcount 변경점 적용
	m_iMaxCount = _iResizeCount;
}

int& CArr::operator[](int idx)
{
	return m_pInt[idx];
}
