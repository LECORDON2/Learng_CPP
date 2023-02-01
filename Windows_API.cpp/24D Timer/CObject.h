#pragma once


class CObject
{
private:
	Vec2  m_vPos;
	Vec2  m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScalse(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	CObject();
	~CObject();
};

// 데이터 단위가 실수라도 렌더링 할때는 정수로 된다.
