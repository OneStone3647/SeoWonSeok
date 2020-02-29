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
	void Update(float CameraX, int FieldIndex);
};

