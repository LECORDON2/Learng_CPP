#pragma once

class CCollider;

class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2	    m_vScale;

	CCollider*  m_pCollider;

	bool		m_bAlive; // 자기자신이 활성화 인지 아닌지 체크하는 멤버


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

	bool IsDeed() { return !m_bAlive; }

	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	// 아무나 오브젝트를 죽이지 않게 하기위해 private, 오로지 이벤트 처리를 통해서만 진행할 것이다.
	// friend class CEventMgr
	void SetDead() { m_bAlive = false; }

public:
	virtual void update() = 0;
	virtual void finalupdate() final; 
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};
