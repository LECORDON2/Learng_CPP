#include <iostream>
#include <vector>  // 표준제공 가변 배열
#include <list>    // 표준제공 연결형 리스트
#include "Clist.h"



int main()
{
	
	// list iterator

	CList<int> mylist;

	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);
	
	CList<int>::iterator listiter = mylist.begin();
	int a = *listiter;
	
	++listiter;
	listiter = mylist.insert(listiter, 150);

	for (listiter = mylist.begin(); listiter != mylist.end(); ++listiter)
	{
		std::cout << *listiter << std::endl;
	}

	

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Clist.h

#pragma once
#include <assert.h>

template<typename T>
struct tListNode
{
	T          data;
	tListNode* pPrev;         
	tListNode* pNext;         
	                          
	tListNode()
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{
	}
	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext) 
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
	void push_front(const T & _data);

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);  
	iterator insert(const iterator& _iter, const T& _data);

public:
	CList();
	~CList();
	
	class iterator
	{
	private:
		CList<T>*     m_pList;
		tListNode<T>* m_pNode;   // null인 경우, end iterator로 간주
		bool          m_bValid;

	public:
		T& operator *()
		{
			return m_pNode->data;
		}

		bool operator ==(const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator !=(const iterator& _otheriter)
		{
			return !(*this == _otheriter);
		}

		iterator& operator ++()
		{
			// end에서 ++ 한 경우
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pNext;
			return *this;
		}

		iterator& operator ++(int)
		{
			iterator copyiter(*this);
			
			++(*this);
			
			return copyiter;
		}


		// 직접해보기
		iterator& operator --()
		{
			// 헤드노드에서 -- 한 경우
			if (m_pList->m_pHead == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pPrev;
			return *this;
		}

		iterator& operator --(int)
		{
			iterator copyiter = (*this);

			--(*this);

			return copyiter;
		}


	public:
		iterator()
			: m_pList(nullptr)
			, m_pNode(nullptr)
			, m_bValid(false)
		{
		}

		iterator(CList<T>* _pList, tListNode<T>* _pNode)
			: m_pList(_pList)
			, m_pNode(_pNode)
			, m_bValid(false)
		{
			if (nullptr != _pList && nullptr != _pNode)
			{
				m_bValid = true;
			}
		}

		~iterator()
		{

		}

		friend class CList;
	};
};

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

template<typename T>
inline typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this, m_pHead);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::erase(iterator& _iter)
{
	// iterator가 end iterator 인 경우
	// 유효성 체크
	// iterator가 다른 리스트를 가리키는 경우
	if (_iter.m_pNode == nullptr || !_iter.m_bValid || _iter.m_pList != this)
	{
		assert(nullptr);
	}
	
	// 지워진 노드가 헤드거나 테일일 경우 리스트의 멤버도 바꾼다
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pNext->pPrev = nullptr;
		m_pHead = _iter.m_pNode->pNext;
	}
	else if (_iter.m_pNode == m_pTail)
	{
		_iter.m_pNode->pPrev->pNext = nullptr;
		m_pTail = _iter.m_pNode->pPrev;
	}
	else
	{
		_iter.m_pNode->pPrev->pNext = _iter.m_pNode->pNext;
		_iter.m_pNode->pNext->pPrev = _iter.m_pNode->pPrev;
	}


	// 지운곳에 들어온 노드를 iterator가 다시 가리키게 한다.
	--m_iCount;
	return iterator(this, _iter.m_pNode->pNext);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::insert(const iterator& _iter, const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
;	}

	// 리스트에 추가되는 데이터를 저장 할 node 생성
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	
	if (_iter.m_pNode == m_pHead)
	{
		// iterator가 가리키는 경우가 헤드노드인 경우
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
		m_pHead = pNode;
	}
	else
	{
		// iterator가 가리키고 있는 노드의 이전으로 가서 
		// 다음 노드 주소 파트를 새로 생성한 노드로 지정
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;

		// iterator가 가리키고 있는 노드의 이전을 새로운 노드로 지정
		// 새로운 노드의 pNext 를 iterator 가 가리키고 있는 노드로 지정
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
	}

	++m_iCount;

	return iterator(this, pNode);
}
