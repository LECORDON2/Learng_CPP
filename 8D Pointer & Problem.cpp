#include <stdio.h>

void Test(int* a)
{
	*a = 500;

}




int main()
{
	// 문제 1
	short sArr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int* pI = (int*)sArr;

	// 괄호는 강제 캐스팅

	int iData = *((short*)(pI + 2));

	printf("%d/n", iData);


	// 답 : 5


	// 문제 2 
	char cArr[2] = { 1, 1 };

	short* pS = (short*)cArr;

	iData = *pS;

	printf("%d/n", iData);

	// 답 : 1 
	// 틀림
	// short는 2byte 정수로 읽기 때문에 char입장에서 1이 아니라 그다음 배열의 byte도 읽기 때문에 257이 나온다.

	int a = 100;

	Test(&a);

	printf("%d/n", a);

	//int Test(int a)
	//{
	//	a = 500;

	//}


	// 위의 주석과 같은 함수라면면 100이 나온다.
	// Test함수 속 a와 main 쪽 a는 다르기 때문에, 각 함수마다 스택 데이터가 다르기 때문
	

	// 그러나 void Test함수로 바꾸면
	// 이러면 main 쪽 a가 바뀐다.


	scanf_s("%d", &a);

	return 0;

}

