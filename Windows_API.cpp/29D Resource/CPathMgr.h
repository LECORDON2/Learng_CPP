#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_szContentPath[255]; // 윈도우에서 경로는 255글자로 제한이 되어 있다.

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; } // init에서 찾은 경로가 훼손되지 않게 하기 위해 const pointer

};
