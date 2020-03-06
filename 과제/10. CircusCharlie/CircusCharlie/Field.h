#pragma once
#include "Bitmap.h"

enum NORMAL
{
	NORMAL_1,
	NORMAL_2
};

class Field
{
private:
	HDC					m_MemDC;

	Bitmap				m_Back;
	Bitmap				m_Deco;

	Bitmap				m_Normal[2];
	int						m_NormalIndex;

	Bitmap				m_Miter;
	int						m_MiterCount;

	float					m_AnimTime;
	float					m_StartAnimTimer;
	float					m_CurAnimTimer;

	bool*					m_bWinFlag;

	float					m_X;

public:
	Field();
	~Field();

public:
	void Init(HDC MemDC, bool* bWinFlag);
	void Update(float x);
};

