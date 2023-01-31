// 열거형
enum MY_TYPE
{
	TYPE_1,  // 0 부터 시작해서 쭉 연결된 숫자로 이해
	TYPE_2,  // 1
	TYPE_3,  // 2
	TYPE_4,
	TYPE_5 = 100, // 직접 숫자 지정가능
	TYPE_6,       // 101이다. 지정한 숫자부터 이어나감
};

enum OTHER_TYPE
{
	TYPE_1, // 이렇게 쓸 수도 있지만 어느쪽 거인지 애매하다.
};

// enum class
enum class CMY_TYPE
{
	CTYPE_1,  
	CTYPE_2,  
	CTYPE_3, 
	CTYPE_4,
	CTYPE_5 = 100, 
	CTYPE_6,       
};

enum class COTHER_TYPE
{
	CTYPE_1, 
};


#define CLASS_1 0
#define CLASS_2 1
#define CLASS_3 2

// enum과 상당히 유사
// 그러나 define은 전처리기이기 때문에 컴파일러 이전에 실행
// 사실상 int a = CLASS_1은 int a = 0 과 동일하다.
// 하지만 int b = (int)CMY_TYPE::CTYPE_1 이라고 쓴다면 타입이 정확히 보인다. 디버깅시 좀 더 많은 정보를 알 수 있다.

int main()
{	
	int a = TYPE_3; // a는 2
	int b = (int)CMY_TYPE::CTYPE_1; // enum class는 이렇게 써야함, 별개의 타입으로 보기 때문에 정수로 캐스팅 해줘야 한다.
 
  return 0; 
}
