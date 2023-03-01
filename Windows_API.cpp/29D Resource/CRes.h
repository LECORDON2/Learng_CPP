#pragma once
class CRes
{
private:
	wstring m_strKey;          // 리소스 키, 리소스의 고유한 ID
	wstring m_strRelativePath; // 리소스 상대경로

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strpath) { m_strRelativePath = _strpath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	~CRes();
};
