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




int main()
{

	int i = 4;
	int iValue = 1;

	for (int j = 0; j < i; ++j)
	{
		iValue *= (j + 2);
	}
	// 함수를 쓰는 이유는 하나의 기능을 함수로 구현해놓고 계속 재활용 하는 것


	// main함수 안쪽의 구문을 위쪽과 같은 함수로 만들면
	int iValue = Factorial(4);

	iValue = Factorial(10);
	
	// 이러하게 필요한 기능들을 쓸때 필요하다.
	// 깔끔하게 편해진다.

	return 0;

}
