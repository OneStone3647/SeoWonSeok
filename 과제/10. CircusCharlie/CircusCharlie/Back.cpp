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
	m_Normal[NORMAL_1].Init(m_BackDC, "Bitmap\\back_normal.bmp");
	m_Normal[NORMAL_2].Init(m_BackDC, "Bitmap\\back_normal2.bmp");
	m_Miter.Init(m_BackDC, "Bitmap\\miter.bmp");

	m_NormalIndex = 0;

	m_bIsWin = false;
	m_AnimTime = 100.0f;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0.0f;
}

void Back::Update(float CameraX, int FieldIndex, bool bWinFlag)
{
	m_CurAnimTimer = GetTickCount();
	m_bIsWin = bWinFlag;

	// �ʵ� �ε����� ���� ����� 3��(��, �߰�, ��)�� �׸���.
	m_MiterCount = 100 - FieldIndex * 10;
	DrawBack(CameraX - FieldWidth * FieldIndex, m_MiterCount);
	DrawBack(CameraX - FieldWidth * (FieldIndex + 1) + 5.0f, m_MiterCount - 10);
	DrawBack(CameraX - FieldWidth * (FieldIndex + 2) + 5.0f, m_MiterCount - 20);
}

void Back::DrawBack(float CameraX, int MiterCount)
{
	TCHAR miter[256];

	// �ٴ� �׸���
	for (int i = 0; i < 7; i++)
	{
		m_Back.Draw(m_BackDC, i * m_Back.GetSize().cx * 2.2f - CameraX, 270, 2.3f, 2.3f);
	}

	// ���� �׸���
	for (int i = 0; i < 12; i++)
	{
		// �̰��� ���
		if (m_bIsWin)
		{
			if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
			{
				m_NormalIndex++;
				if (m_NormalIndex > 1)
				{
					m_NormalIndex = 0;
				}
				m_StartAnimTimer = m_CurAnimTimer;
			}
		}

		m_Normal[m_NormalIndex].Draw(m_BackDC, i * m_Normal[m_NormalIndex].GetSize().cx * 1.4f - CameraX, 176);
	}

	// �ڳ��� �׸���
	m_Deco.Draw(m_BackDC, m_Deco.GetSize().cx * 1.4f - CameraX, 173);

	m_Miter.Draw(m_BackDC, m_Miter.GetSize().cx * 10.0f - CameraX, 600);
	wsprintf(miter, TEXT("   %d   "), MiterCount);
	TextOut(m_BackDC, m_Miter.GetSize().cx * 10.4f - CameraX, 615, miter, strlen(miter));
}
