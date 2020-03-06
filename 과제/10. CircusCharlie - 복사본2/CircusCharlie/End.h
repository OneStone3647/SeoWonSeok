#pragma once
#include "Bitmap.h"

class End
{
private:
	HDC				m_BackDC;

	Bitmap			m_End_Bitmap;

	RECT				m_Collision;

	float				m_X;	
	float				m_Y;

public:
	End();
	~End();

	void Init(HDC BackDC);
	void Update(float CameraX);
	void SetCollision();

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline float GetX()
	{
		return m_X;
	}
	inline float GetY()
	{
		return m_Y;
	}
};

