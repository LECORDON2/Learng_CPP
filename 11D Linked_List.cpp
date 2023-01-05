#include <iostream>
#include "LinkedList.h"

int main()
{

	// 연결형 리스트
	// 데이터가 띄엄띄엄 끊어져 있다.
	// 데이터가 저장되어있는 단위를 노드라고 부름
	// 하나의 노드에는 데이터도 있지만 다음 데이터를 가리키는 주소도 들어있다.
	
	tLinkedList list;

	InitList(&list);

		
	PushFront_Me(&list, 1);
	PushFront_Me(&list, 2);
	PushFront_Me(&list, 3);
	PushFront_Me(&list, 4);
	PushFront_Me(&list, 5);

	PushBack(&list, 100);
	PushBack(&list, 200);
	PushBack(&list, 300);
	PushBack(&list, 400);

	PushFront(&list, 1);
	PushFront(&list, 2);
	PushFront(&list, 3);
	PushFront(&list, 4);
	PushFront(&list, 5);

	
	ReleaseList(&list);

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LinkedList.h

#pragma once

typedef struct _tagNode
{
	int iData;
	_tagNode* pNextNode;
}tNode;

//typedef struct _tagNode
//{
//	int iData;
//	tNode* pNextNode;
//}tNode;
// 정의 tNode라는 구조체를 정의하는 과정중에서 tNode라는 말을 쓰면 안된다. 

typedef struct _tagList
{
	tNode* pHaedNode;
	int iCount;

}tLinkedList;

// 연결형 리스트 초기화
void InitList(tLinkedList* _pList);

// 연결형 리스트 데이터 추가
void PushBack(tLinkedList* _pList, int _iData);
void PushFront(tLinkedList* _pList, int iData);
void PushFront_Me(tLinkedList* _pList, int iData);

// 연결형 리스트 메모리 해제
void ReleaseList(tLinkedList* _pIist);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LinkedList.cpp

#include <iostream>
#include "LinkedList.h"


void InitList(tLinkedList* _pList)
{
	_pList->pHaedNode = nullptr;
	_pList->iCount = 0;
}

void PushBack(tLinkedList* _plist, int _iData)
{
	// 데이터를 저장할 노드 생성
	// 데이터 복사
	tNode* pNode = (tNode*)malloc(sizeof(tNode));
	pNode->iData = _iData; // 가장 마지막에 들어감 
	pNode->pNextNode = nullptr;

	// 추가한 데이터 처음인지 아닌지 확인
	if (0 ==_plist->iCount)
	{
		_plist->pHaedNode = pNode;
	}
	else
	{
		// 현재 가장 마지막 노드를 찾아서
		// 해당 노드의 pNest를 생성시킨 노드의 주소로 채움
		tNode* pCurfinalNode = _plist->pHaedNode;
		while (true)
		{
			if (nullptr == pCurfinalNode->pNextNode)
			{
				break;
			}
			pCurfinalNode = pCurfinalNode->pNextNode;
		}
		//while (pCurfinalNode->pNextNode)
		//{
		//	pCurfinalNode = pCurfinalNode->pNextNode;
		//}
		// 이렇게만 해도 됨

		pCurfinalNode->pNextNode = pNode;

	}
	++_plist->iCount;
}

void PushFront(tLinkedList* _pList, int iData)
{
}

// 재귀 함수 버전
//void Release(tNode* _pNode)
//{
//	if (nullptr == _pNode)
//	{
//		return;
//	}
//	Release(_pNode->pNextNode);
//	free(_pNode);
//}
//
//void ReleaseList(tLinkedList* _pList)
//{
//	Release(_pList->pHaedNode);
//}

void PushFront(tLinkedList* _pList, int _iData)
{
	// 새로 생성시킨 노드의 다음을 기존의 헤드로 지정한다.
	tNode* pNewNode = (tNode*)malloc(sizeof(tNode));
	pNewNode->iData = _iData;
	pNewNode->pNextNode = _pList->pHaedNode;
	
	// 리스트의 헤드노드 포인터를 갱신한다.
	_pList->pHaedNode = pNewNode;

	// 데이터 카운트 증가
	++_pList->iCount;
}

// 과제 만들기
void PushFront_Me(tLinkedList* _pList, int _iData)
{
	// 1. 새로운 노드와 데이터 추가하기
	tNode* pNode = (tNode*)malloc(sizeof(tNode));
	pNode->iData = _iData; 	
	
	// 2. 처음 데이터인지 체크
	if (_pList->iCount == 0)
	{
		_pList->pHaedNode = pNode;
		pNode->pNextNode = nullptr;
	}
	else
	{
		// 3. 추가 되어지는 노드의 넥스트 노드는 이전의 헤드노드의 주소가 들어가 있어야 함
		pNode->pNextNode = _pList->pHaedNode;
		
		// 4. 리스트의 헤드노드가 되어야함
		_pList->pHaedNode = pNode;
	}
	++_pList->iCount;
}

void ReleaseList(tLinkedList* _pList)
{
	tNode* pDeleteNode = _pList->pHaedNode;

	while (pDeleteNode) // pDeleteNode가 0이 되는 순간 즉 false
	{
		tNode* pNext = pDeleteNode->pNextNode;
		free(pDeleteNode);
		pDeleteNode = pNext;
	}
}
Footer
© 2023 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
Statu
