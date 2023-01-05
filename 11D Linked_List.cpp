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

	PushBack(&list, 100);
	PushBack(&list, 200);
	PushBack(&list, 300);
	PushBack(&list, 400);

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
