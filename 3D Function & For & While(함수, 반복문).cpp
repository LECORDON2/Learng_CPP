
// 전처리기 구문 : 모든 컴파일 구문에서 먼저 수행?
#define HUNGRY 0x01
#define THIRSTY 0x02
#define TIRED 0x04
#define FIRE 0x08

#define COLD 0x010
#define POISon1 0x020
#define POISon2 0x040
#define POISon3 0x080

#define POISon4 0x100
#define POISon5 0x200
#define POISon6 0x400
#define POISon7 0x800





// 0x는 16진수라는 것
// 세번째 칸에 들어가야 되니 4가 된다.


// 장점: 가독성, 일일히 마꾸지 않아도 된다(유지보수).


// 주석으로 처리되는 글자들은슬래쉬 두개를 쓴다
// 코드로 인식되지 않음

// 전역변수

int global = 0;

int ADD(int left, int right)
{
	retrun left = right;
}

// 반환 타입은 int
// ADD라는 함수 안쪽의 left, right는 지역 변수이다.

// 함수
int main()
{

	
	
	// 변수
	// 변수명 규칙
	
	// 1. 지역 변수
	// 괄호 안의 변수는 지역 변수
	// 이 안쪽은 main이라는 함수 구문안의 지역변수들이다.

	// 2. 전역변수
	// 함수 바깥에 선언되어 있는 변수들
	
	// 3. 정석변수
	
	// 4. 외부변수

	
	// 지역변수
	int iName = 0;
	
	// 괄호 안에 선언된 변수(함수, 지역)

	{
		// main이라는 함수안에서 만들어진 세부 영역

		int iName = 100;
		// 바깥에 같은 변수명을 가진 변수가 있어도 괄호안의 경우는 문제 되지 않는다
		// 이렇게 되면 우선순위는 이 지역을 우선한다.
		iName;
		{

			{

				// 지역안의 지역도 됨
			}
		}
		// 밖으로 벗어나면 바깥쪽 변수가 된다.
	}



	int iName = 100;
	// 위에 이미 있는데 똑같은 이름으로 변수 지을수 있을까?
	// 안된다. 에러가 뜸




	// 함수
	// 여러작은 기능이 모여 작동하는게 모듈화?

	data = ADD(10, 20)
	// 결과는 30
	// 함수는 바깥 쪽에





	return 0;
}



#include <stdio.h>
// printf와 scanf를 쓰기위한 표준 입출력함수 헤더를 참조


// 함수
int main()
{

	printf();
	scanf();
	int iData = ADD(100, 200);

	printf("Hello World");


	// 반복문
	// for()
	// while()

	for ( /*반복자 초기화*/ ; /*반복자 조건 체크(참 또는 거짓)*/ ; /*반복자 변경*/)
	{

	}



	for (int i = 0;i < 4 ; ++i)
	{

		printf("Hello World\n");
		// \n \(역슬래시)n은 콘솔창에서 다음줄로 가라는 의미
		// 네줄로 출력됨

		continue;
		// 반복구문이 수행되는 도중 continue를 만나면 뒤를 더이상 수행하지 않고 반복자 변경파트로 넘어감

		break;
		// 만나자 마자 반복문이 끝나버림, 밖으로 나감

	}
	// 처음에 i는 0이고 중간 조건체그가 성공하고 for문이 실행되고 마지막으로 옴 1로 증가 이런식으로 계속돈다.
	// i가 0에서 9까지 돈다.


	for (int i = 0;i < 4; ++i)
	{
		if (i % 2 == 1)
		{
			continue;
		}
		printf("Hello World\n");
		// \n \(역슬래시)n은 콘솔창에서 다음줄로 가라는 의미
		// 네줄로 출력됨

		// 위와 같이 continue를 쓰면 홀수 일때는 출력이 안됨

		continue;
		// 반복구문이 수행되는 도중 continue를 만나면 뒤를 더이상 수행하지 않고 변경파트로 넘어감

		break;
		// 만나자 마자 반복문이 끝나버림, 밖으로 나감


	}



	while (/*조건 체크(어떤 조건이든 참이면 수행된다. 아니면 깨진다.)*/)
	{


	}

	int i = 0;

	while (i < 2)
	{

		printf("Hello World\n");

		++i;
		continue;

		break;
	}

	// 두번 돔


	// 프로그램이 계속 도는 이유는 이러한 반복문이 계속 돌기 때문이다.

	return 0;
	// 전부 반환하고 나면 메인 함수가 종료되고 프로그램이 종료 됨
}
