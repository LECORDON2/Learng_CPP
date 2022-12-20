
// 전처리기 구문 : 모든 컴파일 구문에서 먼저 수행
#define HUNGRY 0x01
#define THIRSTY 0x02
#define TIRED 0x04 // 세번째 칸에 들어가야 되니 4가 된다.
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

// 장점: 가독성, 일일히 마꾸지 않아도 된다(유지보수).

int main()
{
	


	// 비트 연산자
	// 비트 단위로 연산이 진행될때 쓴다
	// 쉬프트 <<, >> : 비트르 한칸 씩 민다
	unsigned char byte = 1;
	byte << 1;
	// 00000001 -> 00000010
	// 이진법에서 한칸 증가하는 것은 두배가 되는 것

	byte <<= 1;
	byte = byte << 1;
	// 좌측으로 한칸 밀고 byte에다 다시 넣는 것

	byte <<= 2; // 2^n의 배수
	// 4배가 되는 것

	byte >>= 1; // 2^n 나눈 몫
	// 절반으로 줄어드는 것, 그런데 나머지는?

	byte = 13;
	byte >>= 1;
	// 나머지는 오른쪽으로 밀리면서 소실 됨, 2로 나눈 몫이다.

	// 비트 곱(&), 합(|), xor(^), 반전(~)
	// 비트단위로 연산을 진행
	// & : 둘다 1인 경우 1
	// | : 둘장 하나라도 1이면 1
	// ^ : 같으면 0, 다르면 1
	// ~ : 1은 0으로, 0은 1로
	// 비트 자리수 대로 연산하는 것
	// 합일때 두비트가 모두 1이면 1, 0이하나라도 있으면 0
	// 반전은 각자리의 비트를 뒤집는것 10010011 -> 01101100
	// xor : 두 비트가 같으면 0 다르면 1이다.


	int iStatus = HUNGRY;
	// 위에서 작성한 #define HUNGRY 0x01에 의해서 HUNGTY = 1이다.


	unsigned int IStatus = 0;
	// 상태 추가
	IStatus |= THIRSTY
	IStatus |= HUNGRY
	
	if (IStatus & THIRSTY)
	{

	}
	// 내가 지정한 자리에만 1인지 물어보는 것
	// THIRSTY는 4이기에 두 번째 자리가 1인데 이것을 IStatus와 & 연산으로 비교하여 해당 자리가 맞으면 1이 나오므로 참이되고 아니면 0이나와 거짓이 된다.

	// 특정 자리 비트 제거
	// 상태 제거
	IStatus &= ~THIRSTY;
	// 반전 시키고 & 연산을 하면 된다.
	// IStatus가 11011001이라고 가정한다. THIRSTY는 4이므로 이를 반전시키면 11111101이 된다. 그리고 이 둘을 &으로 연산하면, 원래 IStatus에서 0이었던 비트는
	// 0이되고 1이었던 비트는 1이된다. 그리고 THIRSTY에서 원래 1이었던 비트는 반전시켰기 때문에 0이된다. 고로 이러한 방식으로 특정한 자리의 비트를 제거할 수 있다.



	// 비트가 32개 니까 특정 상태를 32개 표현할 수 있다.
	// ex) 첫번째 칸이 0이면 배고프다. 1이면 배부르다 등







	return 0;
}
