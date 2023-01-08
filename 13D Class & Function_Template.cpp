// CArr.h의 클래스의 변경

// 템플릿의 함수들은 헤더파일어 있어야 한다.
// 구현 부분의 함수들도 전부 헤더에 있어야 한다.
CArr.h 가정

template<typename T>
class CArr
{
private:
	T* m_pData;
	int m_iCount;
	int m_iMaxCount;
public:
	void push_back(const T& _Data);
	void resize(int _iResizeCount);

	T& operator[] (int idx);
	CArr();
	~CArr();
};


#include <assert.h>


template<typename T>
CArr<T>::CArr()                        // CArr안의 클래스의 T버전 안에 구현된 생성자를 지칭하는 것
	: m_pInt(nullptr)
	, m_iCount(0)
	, m_iMaxCount(0)
{
	m_pInt = new T[2];          
}

template<typename T>
CArr<T>::~CArr()
{     
	delete[] m_pData;
}

template<typename T>
void CArr<T>::push_back(const T& _Data)
{
	
	if (m_iMaxCount <= m_iCount) 
	{
		resize(m_iMaxCount * 2);
	}
	
	m_pInt[m_iCount++] = _iData;
}

template<typename T>
void CArr<T>::resize(int _iResizeCount)
{
	
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);
	}

	
	T* pNew = new T[_iResizeCount];

	
	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_pInt[i];
	}
	delete[] m_pInt;
	m_pInt = pNew;
	m_iMaxCount = _iResizeCount;
}

template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}

// CArr<int> carr;
// CArr<float> carr;
// 이 가능하다.

template<typename T>  // T 부분이 변경
T Add(T a, T b)
{
	return a + b;
}

// int Add(int a, int b)
// {
//	 return a + b;
// }
//
// float Add(float f, float f1)
// {
//	 return f + f1;
// }

int main()
{
	// 함수 템플릿
	int i = Add<int>(10, 20);
	// 틀만 선언하고 사용하지 않으면 함수는 만들어 지지 않는다.
	// Add는 함수가 아니라 함수 템플릿

	// 클래스 템플릿

	return 0;
}
