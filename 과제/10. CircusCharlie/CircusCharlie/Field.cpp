#include "Field.h"



Field::Field()
{
}


Field::~Field()
{
}

void Field::Init(HDC MemDC, bool* bWinFlag)
{
	m_MemDC = MemDC;

	m_Back.Init(m_MemDC, "Bitmap\\back.bmp");
	m_Deco.Init(m_MemDC, "Bitmap\\back_deco.bmp");

	m_Normal[NORMAL_1].Init(m_MemDC, "Bitmap\\back_normal.bmp");
	m_Normal[NORMAL_2].Init(m_MemDC, "Bitmap\\back_normal.bmp");
	m_NormalIndex = NORMAL_1;

	m_Miter.Init(m_MemDC, "Bitmap\\miter.bmp");
	m_MiterCount = 100;

	m_AnimTime = 100;
	m_StartAnimTimer = GetTickCount();
	m_CurAnimTimer = 0;

	m_bWinFlag = bWinFlag;

	m_X = 0;
}

void Field::Update(float x)
{
	if (*m_bWinFlag)
	{
		m_CurAnimTimer = GetTickCount();
	}

	// �ٴ� �׸���
	for (int i = 0; i < 7; i++)
	{
		m_Back.OriginDraw(m_MemDC, x + i * m_Back.GetSize().cx * 2.2f, 270.0f, 2.3f, 2.3f);
	}

	// ���� �׸���
	for (int i = 0; i < 11; i++)
	{
		// �̰��� ���
		if (*m_bWinFlag)
		{
			if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
			{
				m_NormalIndex++;
				if (m_NormalIndex > NORMAL_2)
				{
					m_NormalIndex = NORMAL_1;
				}
				m_StartAnimTimer = m_CurAnimTimer;
			}
		}

		m_Normal[m_NormalIndex].OriginDraw(m_MemDC, x + i * m_Normal[m_NormalIndex].GetSize().cx * 1.45f, 176.0f);
	}

	// �ڳ��� �׸���
	m_Deco.OriginDraw(m_MemDC, x + m_Deco.GetSize().cx * 1.5f, 172.0f);

	float miterPos = (m_Back.GetSize().cx * 7 * 2.2f - m_Miter.GetSize().cx * 1.5f) / 2;
	// ���ͱ� �׸���
	m_Miter.OriginDraw(m_MemDC, x + miterPos, 600.0f);
	TCHAR miter[256];
	m_MiterCount = 100;
	wsprintf(miter, TEXT("   %d   "), m_MiterCount);
	TextOut(m_MemDC, x + miterPos + 20.0f, 615, miter, strlen(miter));
}
