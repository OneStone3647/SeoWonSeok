#pragma once
#include "Bitmap.h"

class Back
{
private:
	HDC				m_BackDC;
	//HDC				m_MemDC;
	//HBITMAP			m_NewBitmap;
	//HBITMAP			m_OldBitmap;

	Bitmap			m_Back;
	Bitmap			m_Deco;
	Bitmap			m_Normal1;
	Bitmap			m_Normal2;

public:
	Back();
	~Back();

	void Init(HDC BackDC);
	void Update();
	void DrawBack();
};

