#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>



// 메모리 영역
// 1. 스택 : 함수가 변수사용할때 쓰는 영역
// 2. 데이터 
// 3. 힙
// 4. ROM(코드)


// 함수 오버로딩
// 함수 오버라이딩하고는 다르다.
void Test(int a)
{


}

void Test(int a, int b)
{


}

void Test(float a)
{


}

// 함수의 이름이 같이만 인자의 갯수가 다르기 때문에 컴파일러가 어떤 함수를 호출할지 결정할 수 있다.
// 혹은 인자수가 같더라도 하나는 실수라면 구분한다.
// 이것을 함수 오버로딩이라고 한다.



unsigned int GetLength(const wchar_t* _pStr) // 문자열의 길이를 알아내는 함수
{
	// 문자열 횟수 체크
	int i = 0;


	while (true)
	{
		wchar_t c = *(_pStr + i); // _pSter + i = _pStr[i]

		if ('\0' == c) // NUL문자는 역슬래시 0 혹은 정수 0
		{
			break;
		}

		++i;

	}

	//while ('\0' != _pStr[i])
	//{

	//	++i

	//}
	// 이러한 방법도 가능하다.



	return i;
	// _pSter[0]; // main에서 szName[0]에 해당, 값을 확인하는 것만 가능


}


void StrCat(wchar_t* _pDest, unsigned int _iBufferSize, const wchar_t* _pSrc)
{
	// 경고 발생시키는 함수 호출
	// assert(nullptr); // 헤더 참조 #include <assert.h>

	// 예외 처리
	// 이어붙인 최종 문자열 길이가, 목적지 저장 곤간을 넘어서려는 경우
	int iDestlen = GetLength(_pDest);
	int iSrclen = GetLength(_pSrc);
	if (_iBufferSize < iDestlen + iSrclen + 1) // + 1은 NUL문자 공간
	{
		assert(nullptr);

	}

	// 문자열 이어 붙이기
	// 1. 목적지 문자열의 끝을 확인(문자열이 이어 붙을 시작 위치)
	iDestlen; // Dest 문자열의 끝 인덱스
	

	// 2. 반복적으로 Src 문자열을 Dest 끝 위치에 복사하기
	// 3. Src 문자열의 끝을 만나면 반복 종료
	for (int i = 0; i < iSrclen + 1; ++i)  // NULL까지 넣기 위해서 + 1을 한다.
	{
		_pDest[iDestlen + 1] = _pSrc[i];
	}

	

}


int main()
{
	wchar_t szName[10] = L"Raimond";

	// 문자열 길이 구하기
	// int iLen wcslen(szName);
	int iLen = GetLength(szName);
	// 이러면 7이 나옴

	// 문자열 이어 붙이기
	wchar_t szString[100] = L"abc";
	
	// wcscat_s(); 
	// 이어붙임을 당하는 쪽은 변해야 해서 const가 아니고 붙여지는 쪽은 읽어오기만 하면 되서 const를 붙인다. 
	wcscat_s(szString, 100, L"def"); // def는 읽기 전용에 있는 문자열주소이다. const point이다.
	wcscat_s(szString, 100, L"gef"); // 계속 이어붙는다.

	return 0;

}



// 문자
// 문자일 때 작은 따옴표
// 문자열일 때 쌍 따옴표
char c = 0; // 숫자에 대응하는 문자도 같이 보여줌
// 1byte 정수 타입
bool b = 1; // true로 보여줌

wchar_t wc = 49; // 2byte 49와 1 둘다 보여줌, 아스키 코드에서 숫자 49는 문자 1
short s = 49; // 49만 보여줌

// 문자이미지를 저장해 놓은 표가 죤재하는 것
// 문자에 대응되는 숫자가 있다.

// 메모리에서 1;과 문자1은 다르다

char c = 1; 
c = '1'; // 49가 들어가 있다.

wc = 459; // 459를 이진수로 표현한 것
"459"; // 문자가 하나하나 나열된 것, 한칸한칸은 1바이트로 되어있을 것이다. 아스키 코드 상에서 52, 53, 57
// 문자 하나하나당 해당하는 코드가 있다.

// 문자가 어디까지 나열되어있는 것인지 정해야 한다(메모리 상에서).
// 문자의 끝이다라는 의미의 용도로 0을 넣어야한다.
// 0에 대응하는 문자가 NUL문자이다. 
// 공백을 의미하는 SP와는 다르다. SP는 32이다.
// 따옴포 끝에 보이지 않지만 NUL문자가 있는 것


{

	// 문자
	// char(1), wchar(2)
	// 1바이트로 매핑시킬수 있는 문자는 127가지 이다.
	char c = 'a';
	wchar_t wc = L'a'; // L은 문자를 2바이트 단위로 쓴다는 의미
	char szChar[10] = "abcdef";
	wchar_t szWChar[10] = L"abcdef"; // 문자열에 적혀있는 데이터를 우리쪽 배열로 옮겨오겠다.
	// 배열의 메모리 전체는 20byte이다. 
	// "abcdef" 즉 6개니까 6개의 배열만 팔요하다고 생각해서 [6]을 적는 다면 오류가 난다.
	// 문자열의 끝에는 NUL이 필요하기 때문이다.
	// 위와 같은 초기화법은 문자전용에만 통한다.
	short arrShort[10] = L"abcdef"; // 정수형 표현 자료이기 때문에 안된다.
	short arrlShort[10] = [97, 98, 99, 100, 101, 102]; // 이것은 가능하다.

	const wchar_t* pChar = L"abcdef";
	// 문자열의 정체는 주소 값
	// 문자 a의 시작주소를 받아온 것
	// 다이렉트로 문자를 가리키는 것이다.
	
	szWChar[1] = 'z';
	// 배열의 b가 z로 바뀐것
	pChar[1] = 'z';
	// *(pChar + 1) = 'z';와 같은 것
	// 실시간으로 코드를 수정하는 것
	// 코드는 Read only 메모리에 있어서 수정할 수 없다.

	// 그래서 수정할 수 없는 const pointer로 받아옴




	char szTest[10] = "abc한글";
	// L이 없다고 모든 문자가 1byte가 아니라 가변적 : 멀티 바이트 문자 셋, 표준적인 방식이 아니다.
	// 유니코드 시스템이 여러가지로 유리함
	// 앞으로 2byte방식을 사용할 것

	wchar_t szTestW[10] = L"abc한글";



}



{
	// 문자 갯수 세는 법, 문자의 길이를 확인하는 함수
	wchar_t szName[10] = L"Raimond";
	// 이 문자열은 읽기 전용영역안에 메모리 초기화 영역에 있디. 
	int iLen = wcslen(szName); // 헤더 참조: #include <wchar.h>
	// 콘스트 포인터를 요구함 : 길이만 확인할뿐 수정할 생각은 없기 때문에
	// 7이라는 결과가 나온다.




}


