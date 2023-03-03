#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HDC         m_dc;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo; // 정보를 받아올 구조체

public:
    void Load(const wstring& _strFilePath);
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }
    HDC GetDC() { return m_dc; }

    // 자체적으로 동적할 수 없게 private로 막고 friend 선언
private:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};
