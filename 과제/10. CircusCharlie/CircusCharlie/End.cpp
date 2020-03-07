#include "End.h"



End::End()
{
}


End::~End()
{
}

void End::Init(HDC MemDC, float FieldWidth)
{
	m_MemDC = MemDC;

	m_EndBitmap.Init(m_MemDC, "Bitmap\\end.bmp");

	m_X = FieldWidth;
	m_Y = 460.0f;

	SetCollision();
}

void End::Update(float * CameraX)
{
	// 디버그 용
	Rectangle(m_MemDC, m_Collision.left, m_Collision.top,
		m_Collision.right, m_Collision.bottom);

	m_EndBitmap.Draw(m_MemDC, m_X * 10 - (*CameraX) + 500.0f, m_Y);
}

void End::SetCollision()
{
	m_Collision.left = m_X + 87.0f;
	m_Collision.right = m_X + 87.0f + m_EndBitmap.GetSize().cx * 1.5f;
	m_Collision.top = m_Y - 50.0f;
	m_Collision.bottom = m_Y + m_EndBitmap.GetSize().cy * 1.5f;
}
