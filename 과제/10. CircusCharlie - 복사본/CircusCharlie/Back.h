#pragma once
#include "Bitmap.h"

enum NORMAL
{
	NORMAL_1,
	NORMAL_2
};

class Back
{
private:
	HDC				m_BackDC;

	Bitmap			m_Back;
	Bitmap			m_Deco;
	Bitmap			m_Normal[2];
	Bitmap			m_Miter;

	int				m_NormalIndex;

	float			m_CameraX;
	int				m_FieldIndex;

	int				m_MiterCount;

	bool			m_bIsWin;
	float			m_AnimTime;
	float			m_StartAnimTimer;
	float			m_CurAnimTimer;

public:
	Back();
	~Back();

	void Init(HDC BackDC);
	void Update(float CameraX, int FieldIndex, bool bWinFlag);
	void Draw();
	void DrawBack(float CameraX, int MiterCount);
};

