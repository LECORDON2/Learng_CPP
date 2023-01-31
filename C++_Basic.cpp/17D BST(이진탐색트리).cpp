#include <iostream>
#include <map> // C++에서 제공하는 red/black 트리
#include <set>
#include <string> // 문자열을 다루는
#include"CBST.h"

using std::map;
using std::make_pair;
using std::set;
using std::wcout;
using std::cout;
using std::endl;
using std::wstring;

int main()
{	
	CBST<int, int> bstint;

	bstint.insert(make_bstpair(100, 0)); //           100
	bstint.insert(make_bstpair(150, 0)); //      50           150
	bstint.insert(make_bstpair(50, 0));  //  25      75   125     175
	bstint.insert(make_bstpair(25, 0));  
	bstint.insert(make_bstpair(75, 0));  
	bstint.insert(make_bstpair(125, 0)); 
	bstint.insert(make_bstpair(175, 0)); 

	CBST<int, int>::iterator Iter = bstint.begin();

	Iter = bstint.find(150);
	
	Iter = bstint.erase(Iter);
	

	for (Iter = bstint.begin(); Iter != bstint.end(); ++Iter)
	{
		wcout << Iter->first << Iter->second << endl;
	}

	for (Iter = bstint.find(175); Iter != bstint.begin(); --Iter)
	{
		wcout << Iter->first << Iter->second << endl;
	}

	// 중위 순회 기준으로 특정 노드 다음의 노드를 중위 후속자(in order successor)라고 말함, 
	// 이전은 중위 선행자(in order predecessor)

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CBST.h

#pragma once
#include <assert.h>

enum class NODE_TYPE
{
	PARENT,  // 0
	LCHILD,  // 1
	RCHILD,  // 2
	END,     // 3
};

template <typename T1, typename T2>
struct tPair
{
	T1 first;
	T2 second;
};

template <typename T1, typename T2>
tPair<T1, T2> make_bstpair(const T1& _first, const T2& _second)
{
	return tPair<T1, T2>{_first, _second }; // 중괄호는 구조체 초기화
}

template <typename T1, typename T2>
struct tBSTNode
{
	// data
	tPair<T1, T2> pair;

	tBSTNode* arrNode[(int)NODE_TYPE::END]; // enum을 인덱스처럼 활용

	bool IsRoot()
	{
		if (arrNode[(int)NODE_TYPE::PARENT] == nullptr)
		{
			return true;
		}
		return false;
	}

	bool IsLeftChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
		{
			return true;
		}
		return false;
	}

	bool IsRightChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
		{
			return true;
		}
		return false;
	}

	bool IsLeaf()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::LCHILD] && nullptr == arrNode[(int)NODE_TYPE::RCHILD])
		{
			return true;
		}
		return false;
	}

	bool IsFull()
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] && arrNode[(int)NODE_TYPE::RCHILD])
		{
			return true;
		}
		return false;
	}

	tBSTNode()
		: pair()
		, arrNode{}
	{}

	tBSTNode(const tPair<T1, T2>& _pair, tBSTNode* _pParent, tBSTNode* _pLChild, tBSTNode* _pRChild)
		: pair(_pair)
		, arrNode{_pParent, _pLChild, _pRChild}
	{}
};

template <typename T1, typename T2>
class CBST
{

private:
	tBSTNode<T1, T2>* m_pRoot;    // 루트 노드 주소
	int               m_iCount;   // 데이터 개수


public:
	bool insert(const tPair<T1, T2>& _pair);
	tBSTNode<T1, T2>* GetInorderSuccessor(tBSTNode<T1, T2>* _pNode);
	tBSTNode<T1, T2>* GetInorderPredecessor(tBSTNode<T1, T2>* _pNode);
	
	class iterator;

public:
	iterator begin();
	iterator end();
	iterator find(const T1& _find);
	iterator erase(const iterator& _iter);

private:
	tBSTNode<T1, T2>* DeleteNode(tBSTNode<T1, T2>* _pTargetNode);

public:
	CBST()
		: m_pRoot(nullptr)
		, m_iCount(0)
	{
	}

	// iterator
public:
	class iterator
	{
	private:
		CBST<T1, T2>*	  m_pBST;
		tBSTNode<T1, T2>* m_pNode; // null인 경우 end iterator

	public:
		bool operator ==(const iterator& _other)
		{
			if (m_pBST == _other.m_pBST && m_pNode == _other.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator !=(const iterator& _other)
		{
			return !(*this == _other);
		}

		const tPair<T1, T2>& operator *() // 값을 바꾸면 구조가 틀어질 수도 있기 때문에 const
		{
			// m_pNode nullptr 체크(end iterator인지 아닌지)
			assert(m_pNode); // Node가 nullptr이면 assert에 걸린다. assert()안이 nullptr이면 걸린다.
			
			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator ->() 
		{
			assert(m_pNode); 

			return &m_pNode->pair;  // pair의 주소를 받았다.
		}

		iterator& operator ++()
		{
			m_pNode = m_pBST->GetInorderSuccessor(m_pNode);
			return *this;
		}

		iterator& operator --()
		{
			m_pNode = m_pBST->GetInorderPredecessor(m_pNode);
			return *this;
		}

	public:
		iterator()
			: m_pBST(nullptr)
			, m_pNode(nullptr)
		{}

		iterator(CBST<T1, T2>* _pBST, tBSTNode<T1, T2>* _pNode)
			: m_pBST(_pBST)
			, m_pNode(_pNode)
		{}

		friend class CBST<T1, T2>;
	};
};

template<typename T1, typename T2>
inline bool CBST<T1, T2>::insert(const tPair<T1, T2>& _pair)
{
	tBSTNode<T1, T2>* pNewNode = new tBSTNode<T1, T2>(_pair, nullptr, nullptr, nullptr);

	// 첫번재 데이터 라면
	if (nullptr == m_pRoot)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		tBSTNode<T1, T2>* pNode = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;
		
		while (true)
		{
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			else  // 같다면, 중복값을 허용하는 맴은 multi map 일반적인 map은 무시함
			{
				return false;
			}
			
			if (nullptr == pNode->arrNode[(int)node_type])
			{
				pNode->arrNode[(int)node_type] = pNewNode;
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];
			}
			
			
		}


	}

	// 데이터 개수 증가
	++m_iCount;

	return true;
}

template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInorderSuccessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* pSuccessor = nullptr;
	
	// 1. 오른쪽 자식이 있는 경우, 오른쪽 자식으로 가서, 왼쪽 자식이 없을때 까지 내려감
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	
	// 2. 부모로 부터 왼쪽자식일 때까지 위로 올라감
	//    그때 부모가 후속자
	else
	{
		pSuccessor = _pNode;
		while (true)
		{
			// 더이상 위쪽으로 올라갈 수없다. ==> 마지막 노드였다. 
			if (pSuccessor->IsRoot())
			{
				return nullptr; // end iterator
			}
			// 부모로 부터 왼쪽 자식인지 체크
			if (pSuccessor->IsLeftChild())
			{
				// 그때 부모가 후속자
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
					break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}
		}

	}

	return pSuccessor;
}

template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInorderPredecessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* Predecessor = nullptr;

	// 1. 왼쪽 자식이 있을 경우, 왼쪽 자식으로 가서 오른쪽 자식이 없을때까지 내려감
	if (nullptr !=_pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		Predecessor = _pNode->arrNode[(int)NODE_TYPE::LCHILD];

		while (Predecessor->arrNode[(int)NODE_TYPE::RCHILD])
		{
			 Predecessor = Predecessor->arrNode[(int)NODE_TYPE::RCHILD];
		}
		
	}

	// 2. 부모로 부터 오른쪽 자식일때까지 올라감, 부모로 부터 오른쪽 자식일때 부모가 중위 선행자
	else
	{
		Predecessor = _pNode;

		while (true)
		{
			if (Predecessor->IsRoot())
			{
				return nullptr;
			}

			if (Predecessor->IsRightChild())
			{
				Predecessor = Predecessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				Predecessor = Predecessor->arrNode[(int)NODE_TYPE::PARENT];
			}
		}
	}

	return Predecessor;
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::begin() // 반환타입이 본인 내의 inner class일 경우 tpyename을 적어 줘야 한다.
{
	tBSTNode<T1, T2>* pNode = m_pRoot;

	while (pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::end()
{

	return iterator(this, nullptr);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::find(const T1& _find)
{
	tBSTNode<T1, T2>* pNode = m_pRoot;
	NODE_TYPE node_type = NODE_TYPE::END;

	while (true)
	{
		if (pNode->pair.first < _find)
		{
			node_type = NODE_TYPE::RCHILD;
		}
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		else  // 같다면, 원하는 값을 찾은 것, pNode가 현재 찾으려는 노드다.
		{
			break;
		}

		if (nullptr == pNode->arrNode[(int)node_type])
		{
			// 못찾은 것. pNode = nullptr ==> end iterator
			pNode = nullptr;
			break;
		}
		else
		{
			pNode = pNode->arrNode[(int)node_type];
		}


	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::erase(const iterator& _iter)
{
	assert(this == _iter.m_pBST);

	tBSTNode<T1, T2>* pSccessor = DeleteNode(_iter.m_pNode);

	return iterator(this, pSccessor);
}

template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::DeleteNode(tBSTNode<T1, T2>* _pTargetNode)
{
	// 삭제시킬 노드의 후속자 노드를 찾아 둔다.
	tBSTNode<T1, T2>* pSuccessor = GetInorderSuccessor(_pTargetNode);

	// 1. 자식이 하나도 없는 경우
	if (_pTargetNode->IsLeaf())
	{
		// 삭제할 노드가 루트였다.(자식이 없고 루트 ==> BST 안에 데이터가 1개밖에 없다.)
		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = nullptr;
		}
		else
		{
			// 부모노드로 접근. 삭제될 노드인 자식을 가리키는 포인터를 nullptr로 만든다.
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr;
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr;
			}
		}
		delete _pTargetNode;
			
		// 데이터 개수 맞춰줌
		--m_iCount;
	}

	// 2. 자식이 2개인 경우
	else if (_pTargetNode->IsFull())
	{	
		// 삭제 될 자리에 중위 후속자의 값을 복사시킨다.
		_pTargetNode->pair = pSuccessor->pair;

		// 중위 후속자 노드를 삭제한다.
		// 재귀함수 활용
		// 데이터 개수가 계속 빠질 수 있는 것에 주의, --m_iCount를 1, 3 번 케이스로 옮겨야 한다.
		DeleteNode(pSuccessor);

		// 삭제될 노드가 중위 후속자 노드가 됨
		pSuccessor = _pTargetNode;
	}

	// 3. 자식이 1개인 경우
	else
	{
		// 삭제시킬 노드의 후속자 노드를 찾아 둔다.
		pSuccessor = GetInorderSuccessor(_pTargetNode);

		NODE_TYPE eChildType = NODE_TYPE::LCHILD;
		if (_pTargetNode->arrNode[(int)NODE_TYPE::RCHILD])
		{
			eChildType = NODE_TYPE::RCHILD;
		}

		// 삭제할 노드가 루트였다.
		if (_pTargetNode == m_pRoot)
		{
			// 자식노드(1개)를 루트로 만든다.
			m_pRoot = _pTargetNode->arrNode[(int)eChildType];
			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
		}
		else
		{
			// 삭제될 노드의 부모와, 삭제될 노드의 자식을 연결해준다.
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}
			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = _pTargetNode->arrNode[(int)NODE_TYPE::PARENT];
		}
		delete _pTargetNode;

		// 데이터 개수 맞춰줌
		--m_iCount;
	}

	return pSuccessor;
}
