#pragma once
#include "Bitmap.h"

class End
{
private:
	HDC					m_MemDC;
	
	Bitmap				m_EndBitmap;

	float					m_X;
	float					m_Y;

	RECT					m_Collision;

public:
	End();
	~End();

public:
	void Init(HDC MemDC, float FieldWidth);
	void Update(float* CameraX);
	void SetCollision();

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline float GetX()
	{
		return  m_X;
	}
	inline float GetY()
	{
		return m_Y;
	}
};

