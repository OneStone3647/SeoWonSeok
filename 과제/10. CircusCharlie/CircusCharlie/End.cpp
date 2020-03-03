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

	SetCollision();
}

void End::Update(float CameraX)
{
	// 디버그 용
	//m_End_Bitmap.Draw(m_BackDC, m_X - CameraX + FieldWidth * 1 - 130.0f, m_Y);
	//Rectangle(m_BackDC, m_Collision.left, m_Collision.top, 
	//	m_Collision.right, m_Collision.bottom);

	m_End_Bitmap.Draw(m_BackDC, m_X - CameraX + FieldWidth * 10 - 130.0f, m_Y);	
}

void End::SetCollision()
{
	m_Collision.left = m_X + 870.0f;
	m_Collision.right = m_X + m_End_Bitmap.GetSize().cx * 1.5f + 870.0f;
	m_Collision.top = m_Y - 50.0f;
	m_Collision.bottom = m_Y + m_End_Bitmap.GetSize().cy * 1.5f;
}
