#include "End.h"



End::End()
{
}


End::~End()
{
}

void End::Init(HDC BackDC)
{
	m_BackDC = BackDC;

	m_End_Bitmap.Init(m_BackDC, "Bitmap\\end.bmp");

	m_X = FieldWidth;
	m_Y = 460.0f;

	m_Collision.left = m_X;
	m_Collision.right = m_X + m_End_Bitmap.GetSize().cx;
	m_Collision.top = m_Y;
	m_Collision.bottom = m_Y + m_End_Bitmap.GetSize().cy;
}

void End::Update(float CameraX, int FieldIndex)
{
	m_End_Bitmap.Draw(m_BackDC, m_X - CameraX + FieldWidth * 10 - 130.0f, m_Y);
}
