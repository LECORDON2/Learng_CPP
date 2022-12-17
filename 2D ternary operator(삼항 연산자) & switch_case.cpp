
// 주석으로 처리되는 글자들은슬래쉬 두개를 쓴다
// 코드로 인식되지 않음


int main()
{
	// switch case

	switch (10)
	{
		// switch 해놓고 특정 상수값 및 데이터 값은 넣는다. case와 비교후 일치하는 구문을 실행한다. default는 일치하는 게 없으면 실행됨
		// if else와 유사
	
	case 10:
		break;

	case 20:
		break;

	default:
		break;



	}

	
	// 같은 의미를 if else 구문으로 만들면
	int iTest = 10;

	if (iTest == 10)
	{

	}
	else if (iTest == 20)
	{


	}
	else
	{

	}



	int iTest = 20;

	switch (iTest)
	{

	case 10:
		break;

	case 20:
		// 만약 break없으면 defaualt로 넘어간다. break는 중괄효를 넘어간다는 것, 의도적으로 안쓰는 경우도 있다.

	default:
		break;

	}

	int iTest = 10;

	switch (iTest)
	{

	case 10:
	case 20:
	case 30:
		break;
		
		// 의도적으로 break를 안쓰는 	
		// iTest 안에 있는 값을 10, 20, 30으로 묶는 것, 셋 중 하나만 걸리면 됨
	default:
		break;

	}

	// 위를 if else로 만들면
	if (iTest == 10 || iTest == 120 || iTest == 30)
	{
		// 셋 중하나만 걸리면 실행 된다.
	}
	else
	{

	}


	// 상황에 따라서 선호하는 문법을 사용한다.




	// 삼항 연산자
	// :?

	iTest == 20 ? iTest = 100 : iTest = 200;
	// iTest에 있는 값이 참이면 왼쪽을 수행하고 거짓이면 오른쪽을 수행함
	 
	// 같은 의미로 if else 구문 작성
	if (iTest == 20)
	{
		iTest = 100;
	}
	else
	{
		iTest = 200;
	}


	return 0;
}
