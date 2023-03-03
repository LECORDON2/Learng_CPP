#pragma once

class CCollider;

class CObject
{
private:
	Vec2  m_vPos;
	Vec2  m_vScale;

	CCollider* m_pCollider;


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void update() = 0;
	virtual void finalupdate() final; // 자식에서 오버라이딩을 막아주는 키워드;
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};
