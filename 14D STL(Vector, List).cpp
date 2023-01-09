#include <iostream>
#include "Clist.h"
#include <vector>  // 표준제공 가변 배열
#include <list>    // 표준제공 연결형 리스트

int main()
{
	std::vector<int> vecInt;
	vecInt.push_back(10);
	vecInt.push_back(20);
	vecInt.push_back(30);

	vecInt[0] = 100;   // 연산자 오버로딩 이용한 연산
	vecInt.at(10);     // 위와 같은 의미
	vecInt.data();     // 최초 시작 주소 반환
	vecInt.size();     // 몇개 집어 넣었는지
	vecInt.capacity(); // 현재기준 몇칸까지 허용 범위인지 

	for (size_t i = 0; i < vecInt.size(); ++i) // size_t = long long
	{
		std::cout << vecInt[i] << std::endl;
	}


	std::list<int> listInt;
	listInt.push_front(10);
	listInt.push_back(100);
	listInt.size();

	// iterator(inner class)
	std::list<int>::iterator iter = listInt.begin();
	// list안의 iterator라는 클래스
	// list안의 데이터 중에 첫번째 데이터를 iter가 가리킨다.
	int idata = *iter; // 10이 나옴, iterator안의 *연산자 오퍼레이터가 있을 것이다.

	return 0;

}
