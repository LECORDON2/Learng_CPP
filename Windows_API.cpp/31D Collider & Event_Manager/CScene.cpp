#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
			
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// Dead 상태가 아닌 경우에만 업데이트
			if (!m_arrObj[i][j]->IsDeed())
			{
				m_arrObj[i][j]->update();
			}
			
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// 오브젝트를 삭제해야 하므로 iterator사용
		vector<CObject* >::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			// Dead 상태가 아닌 경우에만 렌더
			if (!(*iter)->IsDeed())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				// 삭제하고 다음 iterator를 받기 때문에 ++iter 생략
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}
