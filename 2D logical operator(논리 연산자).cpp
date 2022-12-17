
// 주석으로 처리되는 글자들은슬래쉬 두개를 쓴다
// 코드로 인식되지 않음


int main()
{


	// 논리 연산자 : !, &&, ||
	// 참(ture)과 거짓(false)
	// ! : 역, 참을 거짓으로 거짓을 참으로 바꾼다 
	// && : 곱, 둘다 참이여야 참, and 
	// || : 합, 돈표시 위에, 둘 중 하나만 참이여도 참, or
	// 참 : 0이 아닌 값, 1로 대답함, 10이든 1이든 참이라고 대답한다. 참 거짓 물어볼 때 참이면 1을 줌
	// 거짓 : 0

	true;
	false;

	int truefalse = true;
	//  이때 truefalse는 1

	int truefalse = false;
	//  이때 truefalse는 0

	bool truefalse = false;
	// bool : true, false만 받아들이는 자료형, 1byte

	bool istrue = 100;
	// 이때는 1로 받아들임 그래서 정수자료형으로 쓰는 것은 곤란

	istrue = true;
	istrue = !istrue;
	// ture가 false로 뒤집힌게 들어옴, 즉 0이다.

	int iTrue = 100;
	iTrue = !iTrue;
	// 이러면 iTrue에는 0이 들어와있다. 참이면 0이 아니고 거짓이면 0인데 참인 100을 뒤집으니 거짓인 0이 된다.

	int iTrue = 0;
	iTrue = !iTrue;
	// 반대로 거짓인 0을 뒤집으면 참이 되는데 이때 참은 1이된다. iTrue는 1이다.

	iTrue = 100 && 200;
	// 둘다 0이 아닌 참이기 때문에 iTrue는 참이 되기에 1이 된다
	
	iTrue = 100 && 0;
	// 이러면 0이 된다. 
	
	iTrue = 0 || 300;
	// 둘중 하나가 참이므로 참 iTure는 1이다. 
	
	iTrue = 0 || 0;
	// 이러면 0이 된다. 





	return 0;
}
