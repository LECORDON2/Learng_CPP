
// 전처리기 구문 : 모든 컴파일 구문에서 먼저 수행?


#include <stdio.h>
// printf와 scanf를 쓰기위한 표준 입출력함수 헤더를 참조


// 함수
int main()
{

	// 콘솔 : 입출력 할 수 있는 창
	// printf
	// scanf
	printf("abcdef %d \n", 10);
	printf("abcdef %f \n", 10);
	// %d는 치환문자 정수를 치환 해 줌
	// %f는 치환문자 실수를 치환 해 줌
	
	for (int i = 0; i < 10; ++i)
	{
		printf("output i : %d \n", i)
	}
	// 결과
	// output i : 1
	// output i : 2
	// output i : 3
	// output i : 4
	// output i : 5
	// output i : 6
	// output i : 7
	// output i : 8
	// output i : 9

	// scanf
	// 콘솔창으로 부터 입력 받음
	int iInput = 0;
	scanf_s("%d", &iInput);
	// 함수 내부에서 무한 루프 돌고 있다.
	// 콘솔창에 입력을 안하기 때문에 계속 돌고 있다.
	// 콘솔창에 100을 넣으면 iInput에 100이 들어온다.

	return 0;

}



