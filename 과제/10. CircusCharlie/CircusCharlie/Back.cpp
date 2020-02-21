#include "Back.h"



Back::Back()
{
}


Back::~Back()
{
}

void Back::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_Back.Init(m_BackDC, "Bitmap\\back.bmp");
	m_Deco.Init(m_BackDC, "Bitmap\\back_deco.bmp");
	m_Normal1.Init(m_BackDC, "Bitmap\\back_normal.bmp");
	m_Normal2.Init(m_BackDC, "Bitmap\\back_normal2.bmp");
}

void Back::Update()
{
	DrawBack();
}

void Back::DrawBack()
{
	// 바닥 그리기
	for (int i = 0; i < 20; i++)
	{
		m_Back.DrawBack(m_BackDC, i * m_Back.GetSize().cx, 300);
	}

	// 관중 그리기
	for (int i = 0; i < 20; i++)
	{
		m_Normal1.DrawBack(m_BackDC, i * m_Normal1.GetSize().cx, 236);
	}

	// 코끼리 그리기
	m_Deco.DrawBack(m_BackDC, m_Deco.GetSize().cx, 233);
}
