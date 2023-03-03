#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDc(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hPen = CCore::Getinst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBRUSHnType)
	: m_hDc(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = CCore::Getinst()->GetBrush(_eBRUSHnType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{

	SelectObject(m_hDc, m_hDefaultPen);
	SelectObject(m_hDc, m_hDefaultBrush);
}
