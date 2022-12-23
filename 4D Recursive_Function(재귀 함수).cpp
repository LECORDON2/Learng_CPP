// 함수
// Factorial
// !8


int Factorial(int _iNum)
{

	int iValue = 1;

	for (int j = 0; j < int _iNum; ++j)
	{
		iValue *= (j + 2);
	}
	return iValue;
}


// 재귀함수
// 함수안에서 자기자신을 호출하는

// 함수 안의 변수들 = 지역 변수
// 디버깅할때 로컬창과 호출스택이 나오는 창 잘 활용하기
// Factorial 호출이 끝나면 호출 스택이 사라짐
// iValue에 값은 언제 전달되는 것인가?
// CPU에 있는 레지스터 메모리에 잠시 받아 놓고 main함수가 꺼내 오는 것


int Factorial(int _iNum)
{

	int iValue = 1;

	for (int j = 0; j < int _iNum; ++j)
	{
		iValue *= (j + 2);
	}
	return iValue;

	Factorial(4);

}


// 함수 안에서 함수를 호출한다면?
// 새로운 Factorial함수가 호출되는 것
// a함수 - b함수 - c함수 - d함수
// 하던 것이 a함수- a함수 - a함수 - a함수 되는 것?
// 그러나 끝도 없이 함수가 쌓이기만 하고 되돌아 오지 않고 스택메모리 한계치에 도달함
// 그런 것을 스택 오버플로우라고 한다.

// 그래서 재귀 함수는 반드시 탈출 조건이 있어야 한다.
// 재귀함수의 장점: 가독성, 구현의 용이
// 단점은 성능이 떨어질 수 있다.


// 재귀함수 팩토리얼
int Factorial_Re(int _iNum)
{
	if (1 == _iNum)
	{
		return 1;
		// return을 만나면 함수 스택이 종료된다.
		// 그렇다면 !1까지 올 것이고 !1 은 1이다.
	}

	return _iNum * Factorial_Re(_iNum - 1);
	// !7 = 7 * !6으로도 볼수 있다.
	// 예를 들어 !7일때 !6을 알아야 한다.
	// 이를 알려주기 위해 자신과 같은 함수를 호출한다.
	// !6 = 6 * !5 이다. 그리고 !5 = 5 * !4 이다 ... 식으로 계속 올라간다.
	// 그렇다면 !1까지 올 것이고 !1 은 1이다.
	// !1의 값이 다시 계속 되돌아 오면서 처음에 물었던 값을 돌려준다.


}


// 피보나치 수열
// 1 1 2 3 5 8 13 21 34 55 ...

int Fibonacci(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}
	// 첫 번재와 두번재는 1이므로

	int iPrev1 = 1;
	int iPrev2 = 1;
	int iValue = 0;

	for (int i = 0; i < _iNum - 2; ++i)
	{
		iValue = iPrev1 + iPrev2;
		iPrev1 = iPrev2;
		iPrev2 = iValue;
		// iPrev2 = iValue;가 먼저 나올 경우 iPrev1에도 같은 값이 들어갈 수 있다.

	}


}

int Fibonacci_Re(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}
	// 첫 번재와 두번재는 1이므로

	// 피보나치 수열 n번째는 n - 1번째와 n - 2번재의 합이다.
	return Fibonacci_Re(_iNum - 1) + Factorial_Re(_iNum - 2);

	// 계속 자신의 합이므로 1까지 올라갔다가 돌아옴?

}




int main()
{


	int iValue = Factorial(4);

	iValue = Factorial(10);
	
	iValue = Factorial_Re(10);

	iValue = Fibonacci(10);
	iValue = Factorial_Re(10);



	return 0;

}
