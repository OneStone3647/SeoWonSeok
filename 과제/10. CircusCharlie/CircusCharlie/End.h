#pragma once
#include "Bitmap.h"

class End
{
private:
	HWND			m_hWnd;

	RECT				m_Collision;

	Bitmap			m_End;

	float				m_X;	
	float				m_Y;

public:
	End();
	~End();
};

