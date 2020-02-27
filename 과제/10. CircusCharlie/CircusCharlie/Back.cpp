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

	m_CameraX = 0.0f;
}

void Back::Update(float PosX)
{
	m_CameraX = PosX;
	m_DrawIndex = m_CameraX / ScreenWidth;
	DrawBack(m_CameraX - ScreenWidth * m_DrawIndex);
	DrawBack(m_CameraX - ScreenWidth * (m_DrawIndex + 1) + 5.0f);
}

void Back::DrawBack(float PosX)
{
	// 바닥 그리기
	for (int i = 0; i < 15; i++)
	{
		m_Back.Draw(m_BackDC, i * m_Back.GetSize().cx * 1.4f - PosX, 240);
	}

	// 관중 그리기
	for (int i = 0; i < 15; i++)
	{
		m_Normal1.Draw(m_BackDC, i * m_Normal1.GetSize().cx * 1.4f - PosX, 176);
	}

	// 코끼리 그리기
	m_Deco.Draw(m_BackDC, m_Deco.GetSize().cx * 1.4f - PosX, 173);
}
