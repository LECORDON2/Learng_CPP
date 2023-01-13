#include <iostream>
#include "Clist.h"
#include <vector>  // 표준제공 가변 배열
#include <list>    // 표준제공 연결형 리스트
#include "CArr_iter.h"

class CTest
{
public:
	int m_i;

public:
	// CTest라는 객체들 끼리 대입이 발생하면 operator 대입 연산자가 호출이 되고
	// 자동으로 만들어지는 기능이다.
	CTest operator =(const CTest& _other)
	{
		m_i = _other.m_i;
		return *this;
	}
public:
	CTest()
		: m_i(0)
	{

	}
	// 복사 생성자, 만들지 않아도 자동으로 생성 됨
	// 생성자를 하나라도 만든 것이 있다면 컴파일러는 기본생성자를 마들어 주지 않는다.
	// 문제가 없으려면 위처럼 만들어 줘야 한다.
	CTest(const CTest& _other)
		: m_i(_other.m_i) // 복사의 원형이 되는 것을 받아와서 초기 값으로 쓰는 것
	{

	}

};

int main()
{
	Darry<int> myvec;
	myvec.push_back(1);
	myvec.push_back(2);
	myvec.push_back(3);
	Darry<int>::iterator myiter = myvec.begin();

	// 자료를 넣다가 공간이 꽉차면 새로운 주소가 할당되는데 이를 iterator도 알아야한다.

	// *myiter
	// ++(전위 후위), --, ==, !=

	int a = 0;
	++a;
	a++;
	// 가장 늦게 연산된다. 연산자체는 전위와 같다.
	// 그러나 멤버함수이므로 일부러 늦게 호출시키는 건 불가능하여
	// 아예 별개의 함수로 만들어야 한다.

	int iData = *(++myiter);

	int iData = *(myiter++);
	// 기본 연산자 처럼 나중에 연산되는 것이 아니라 전위처럼 바로 호출이 되는 것
	// 실제 myiter는 다음 객체를 가리키고 있다.
	// 내부에서는 증가하지 않은 카피본을 준 것이다.
	
	// 지역변수와 리턴 객체가 만들어 졌다 사라지기 때문에 비효율적이다.

	CTest t1;
	t1.m_i = 100;

	// CTest t2;
	// t2 = t1;
	// 위처럼 두번 나누어서 작업할 것이 아니라

	CTest t2(t1);
	// 복사 생성자를 통해서 객체 생성과 대입을 동시에 할 수 있다.

	CTest t3 = t1;
	// 겉으로 보기에는 대입 연산자 처럼 보이지만 
	// 객체가 만들어질 때 t3가 기본 생성자를 호출하고 대입받는 것
	// 이러한 경우에는 컴파일러가 알아서 복사생성자로 처리한다.
	// 출제율 높음


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CArr_iter.h

#pragma once
#pragma once
#include <assert.h>


template <typename T>
class Darry
{
private:
	T* da_pInt;
	int da_iCount;
	int da_iMaxCount;

public:
	void push_back(const T& _Data);
	void resize(int _Resizecount);

	T& operator[](int idx);

	class iterator;    // begin()이 iterator를 모르기 때문에 전방선안한다. 
	iterator begin();  // iterator를 반환 받는다.
	iterator end();


public:
	Darry();
	~Darry();

	// inner 클래스를 포함하고 있는 클래스의 private 멤버에 접근 가능 
	class iterator
	{
	private: // DArry 클래스는 16byte, 그러나 DArry와 iterator는 별개의 자료형
		
		// iterator가 가리킬 데이터를 관리하는 개변배열 주소
		// 자료를 넣다가 공간이 꽉차면 새로운 주소가 할당되는데 이를 iterator도 알아야한다.
		Darry* m_pArr;
		
		// 데이터들의 시작주소
		// iterator가 처음에 받은 주소와 주소가 달라졌는지 감지할 수 있다. 
		// 실제 vector는 이것을 문제로 보고 있다
		T* m_pData;

		// 가리키는 데이터의 인덱스
		// 인덱스가 -1이면 end iterator(스스로 정하는 것)
		int m_iIdx;

	public:
		T& operator * ()
		{
			// iterator가 알고 있는 주소와, 가변 배열이 알고 잇는 주소가 달라진 경우(공간 확장으로 주소가 달라진 경우)
			// iteraotr가 end iterator 인 경우
			if (m_pArr->da_pInt != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}
			return m_pData[m_iIdx];
		}
		
		// 전위
		iterator& operator ++()
		{
			// 2. end iterator인 경우
			// 3. iterator가 알고 있는 주소와, 가변 배열이 알고 잇는 주소가 달라진 경우(공간 확장으로 주소가 달라진 경우)
			if (m_pArr->da_pInt != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}
			// 1. iterator가 마지막 데이터를 가리키고 있는 경우
			// --> end iterator가 된다.
			if (m_iIdx == m_pArr->da_iCount) // 혹은 함수가 있다면 m_pArr->size()
			{
				m_iIdx = -1;
			}
			else
			{
				++m_iIdx;
			}
      
			return *this;
		}

		// ++ 후위, 실제로는 기본연산자처럼 나중에 호출되는게 아닌 바로 호출이 된다.
		// iterator& 로 반환하면 전위와 다를게 없다.
		iterator operator ++(int) // (int)로 인해 후위 연산자로 인식됨
		{
			// (int)로 인해 후위 연산자로 인식됨
			// fake
			// 반환되는건 또다른 복사본
			iterator copy_iter = *this; // 객체를 복사함, 이 경우도 자동으로 만들어진 복사생성자가 만들어진 것

			++(*this);

			// 증가하기 이전의 복사본을 반환
			return copy_iter; 
		}
				
		iterator& operator --()
		{
			// 현재의 인덱스가 가리키는 곳이 첫번째 일 경우와 iterator가 알고 있느 주소와 현재의 주소가 다를 경우
			if (m_pArr->da_pInt != m_pData || m_iIdx == 0)
			{
				assert(nullptr);
			}
			
			if(m_iIdx == -1)
			{
				// end iterator일 경우(마지막 인덱스가 되어야 함, -하면 안됨, 맨 마지막 즉 da_Count - 1 가 되어야함)
				m_iIdx = m_pArr->da_iCount - 1;
			}
			else
			{
				--m_iIdx;
			}
			
			return *this;
		}

		iterator operator --(int)
		{
			iterator copy_iter = *this;

			--(*this);

			return copy_iter;
		}

		// 비교 연산자 ==, !=
		bool operator ==(const iterator& _otheriter)
		{
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
			{
				return true;
			}
			return false;
		}
		bool operator !=(const iterator& _otheriter)
		{
			// if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
			// {
			//	 return false;
			// }
			//return ture;
			return !(*this == _otheriter); // 이런 식으로도 가능하다.
			// *this는 호출시킨 객체
			// == 은 바로 위에 구현한 오퍼레이터
			// ! 는 반대로
		}
		

	public:
		iterator()
			: m_pArr(nullptr)
			, m_pData(__nullptr)
			, m_iIdx(-1)

		{
			// _pArr->da_iMaxCount 이런식으로 inner class 안에서 접근이 가능하다.
		}

		iterator(Darry* _pArr, T* _pData, int _iIdx)
			: m_pArr(_pArr)
			, m_pData(_pData)
			, m_iIdx(_iIdx)
		{

		}

		~iterator()
		{
		}
	};
};


template<typename T>
void Darry<T>::push_back(const T& _Data)
{
	if (da_iCount >= da_iMaxCount)
	{
		resize(da_iMaxCount * 2);
	}
	da_pInt[da_iCount++] = _Data;
}

template<typename T>
void Darry<T>::resize(int _Resizecount)
{
	T* New_Size = new T[_Resizecount];
	for (int i = 0; i < da_iCount; ++i)
	{
		New_Size[i] = da_pInt[i];
	}
	delete da_pInt;
	da_pInt = New_Size;
	da_iMaxCount = _Resizecount;
}

template<typename T>
T& Darry<T>::operator[](int idx)
{
	return da_pInt[idx];
}

template<typename T>
Darry<T>::Darry()
	: da_pInt(nullptr)
	, da_iCount(0)
	, da_iMaxCount(0)
{
	da_pInt = new T[2];
	da_iMaxCount = 2;
}

template<typename T>
Darry<T>::~Darry()
{
	delete[] da_pInt;

}

template<typename T>
typename Darry<T>::iterator Darry<T>::begin()   
{
	if (0 == da_iCount)
	{
		return iterator(this, da_pInt, -1) // 데이터가 엇ㅂ는 경우, begin() == end()
	}
	// typename을 적어준 이유는 반환 타입이 inner class인 iterator이기 때문
	// 시작을 가리키는 iterator를 만들어서 반환해줌
	// 생성자 오버로딩을 통해서 구현 
	// 임시객체를 통해 변수를 만들지도 않느다.
	return iterator(this , da_pInt, 0);  // this는 가변배열의 주소, da_pInt = this->da_pInt
}

template<typename T>
typename Darry<T>::iterator Darry<T>::end()
{
	// 끝의 다음을 가리키는 iterator를 만들어서 반환해줌
	return iterator(this, da_pInt, -1);  // this는 가변배열의 주소, da_pInt = this->da_pInt
}
