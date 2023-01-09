#include <iostream>
#include "Clist.h"


int main()
{
	CList<int> list;
  
	for (int i = 0; i < 4; ++i)
	{
		list.push_back(i);
	}

	// C printf 대체
	std::cout << "안녕" << 10 << std::end1;

	// C scanf 대체
	int iInput = 0;
	std::cin >> iInput;

	return 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Clist.h

#pragma once

// C++ 기준으로는 구조체와 클래스의 차이가 없다고 봐도 된다. 생정자도 만들 수 있다.
// 그러나 구조체는 아무것도 적지않으면 public이다. 클래스는 private이다.
// Node를 클래스로 만들어도 된다.
template<typename T>
struct tListNode
{
	T          data;
	tListNode* pPrev;         // tListNode<T> pNest 라고 적는 것이 원래 맞으나
	tListNode* pNext;         // 본인 내에서는 자기자신을 지칭해도 본인 선언내부에 있기 때문에 알 수 있다.
	                          // 그러나 Clist에서 tListNode* m_HeadNode; 라고 쓰는 것은 안된다.
	tListNode()
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{
	}
	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext) // 생정자도 오버로딩이 가능함
		: data(_data)
		, pPrev(_pPrev)
		, pNext(_pNext)
	{

	}
};                            

template<typename T>
class CList
{
private:
	tListNode<T>* m_pHead;
	tListNode<T>* m_pTail;
	int           m_iCount;

public:
	void push_back(const T& _data);
	void push_front(const T& _data);

public:
	CList();
	~CList();
};

template<typename T>
void CList<T>::push_back(const T& _data)
{
	// 입력된 데이터를 저장할 노드를 동적 할당 함
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, nullptr); // 내가 인자를 줘서 초기화를 해줄 수 있다.
	// 처음 입력된 데이터라면
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		// 데이터가 1개 이상에서 입력 된 경우
		// 현재 가장 마지막 데이터(tail)를 저장하고 있는 노드와
		// 새로 생성된 노드와 서로 가리키게 한다.
		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;
		// List가 마지막 노드의 주소값을 새로 입력된 노드로 갱신한다.
		m_pTail = pNewNode;
		
	}
	// 데이터 개수 증가
	++m_iCount;
}

template<typename T>
void CList<T>::push_front(const T& _data)
{
	// 새로 생성된 노드의 다음을 현재 헤드노드의 주소값으로 채움
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);

	// 현재 헤드노드의 이전노드의 주소값을 새로 생성된 녿드의 주소로 채움
	m_pHead->pPrev = pNewNode;

	// 리스트가 새로 생성된 노드의 주소를 새로운 헤드주소로 갱신한다.
	m_pHead = pNewNode;

	// 데이터 개수 즈가
	++m_iCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 내가 수정한 함수 이렇게 히야 push_front에서 list안이 비어있을 때 오류가 나지 않는다.
template<typename T>
void CList<T>::push_back(const T& _data)
{
	// 입력된 데이터를 저장할 노드를 동적 할당 함
	tListNode<T>* pNewNode = new tListNode<T>(_data, m_pTail, nullptr); // 내가 인자를 줘서 초기화를 해줄 수 있다.
	// 처음 입력된 데이터라면
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		// 데이터가 1개 이상에서 입력 된 경우
		// 현재 가장 마지막 데이터(tail)를 저장하고 있는 노드와
		// 새로 생성된 노드와 서로 가리키게 한다.
		m_pTail->pNext = pNewNode;
		// List가 마지막 노드의 주소값을 새로 입력된 노드로 갱신한다.
		m_pTail = pNewNode;
		
	}
	// 데이터 개수 증가
	++m_iCount;
}

template<typename T>
void CList<T>::push_front(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		// 새로 생성된 노드의 다음을 현재 헤드노드의 주소값으로 채움
		
		// 현재 헤드노드의 이전노드의 주소값을 새로 생성된 녿드의 주소로 채움
		m_pHead->pPrev = pNewNode;

		// 리스트가 새로 생성된 노드의 주소를 새로운 헤드주소로 갱신한다.
		m_pHead = pNewNode;

	}

	// 데이터 개수 즈가
	++m_iCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
CList<T>::CList()
	: m_pHead(nullptr)
	, m_pTail(nullptr)
	, m_iCount(0)
{

}

template<typename T>
CList<T>::~CList()
{
	tListNode<T>* pDeleteNode = m_pHead;

	while (pDeleteNode)
	{
		tListNode<T>* pNext = pDeleteNode->pNext;
		delete(pDeleteNode);
		pDeleteNode = pNext;
	}
}
