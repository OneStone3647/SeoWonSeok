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
	m_CameraX = CameraX;
	m_FieldIndex = FieldIndex;

	m_bIsWin = bWinFlag;
	if (m_bIsWin)
	{
		m_CurAnimTimer = GetTickCount();
	}

	Draw();

	// 필드 인덱스에 따라 배경을 3개(뒤, 중간, 앞)씩 그린다.
	//m_MiterCount = 100 - FieldIndex * 10;
	//DrawBack(CameraX - FieldWidth * (FieldIndex + 1), m_MiterCount);
	//DrawBack(CameraX - FieldWidth * (FieldIndex + 2) + 5.0f, m_MiterCount - 10);
	//DrawBack(CameraX - FieldWidth * (FieldIndex + 3) + 5.0f, m_MiterCount - 20);
}

void Back::Draw()
{
	float newPos = m_CameraX - 500.0f - FieldWidth * m_FieldIndex;

	// 바닥 그리기
	for (int i = 0; i < 7; i++)
	{
		m_Back.Draw(m_BackDC, i * m_Back.GetSize().cx * 2.2f - newPos, 270, 2.3f, 2.3f);
	}

	// 관중 그리기
	for (int i = 0; i < 11; i++)
	{
		// 이겼을 경우
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

		m_Normal[m_NormalIndex].Draw(m_BackDC, i * m_Normal[m_NormalIndex].GetSize().cx * 1.45f - newPos, 176);
	}

	// 코끼리 그리기
	m_Deco.Draw(m_BackDC, m_Deco.GetSize().cx * 1.45f - newPos, 172);

	// 미터기 그리기
	TCHAR miter[256];
	m_MiterCount = 100 - m_FieldIndex * 10;
	m_Miter.Draw(m_BackDC, m_Miter.GetSize().cx * 5.0f - newPos + 20.0f, 600);
	wsprintf(miter, TEXT("   %d   "), m_MiterCount);
	TextOut(m_BackDC, m_Miter.GetSize().cx * 5.4f - newPos + 20.0f, 615, miter, strlen(miter));
}

void Back::DrawBack(float CameraX, int MiterCount)
{
	//TCHAR miter[256];

	//// 바닥 그리기
	//for (int i = 0; i < 7; i++)
	//{
	//	m_Back.Draw(m_BackDC, i * m_Back.GetSize().cx * 2.2f - CameraX, 270, 2.3f, 2.3f);
	//}

	//// 관중 그리기
	//for (int i = 0; i < 12; i++)
	//{
	//	// 이겼을 경우
	//	if (m_bIsWin)
	//	{
	//		if (m_CurAnimTimer - m_StartAnimTimer >= m_AnimTime)
	//		{
	//			m_NormalIndex++;
	//			if (m_NormalIndex > 1)
	//			{
	//				m_NormalIndex = 0;
	//			}
	//			m_StartAnimTimer = m_CurAnimTimer;
	//		}
	//	}

	//	m_Normal[m_NormalIndex].Draw(m_BackDC, i * m_Normal[m_NormalIndex].GetSize().cx * 1.4f - CameraX, 176);
	//}

	//// 코끼리 그리기
	//m_Deco.Draw(m_BackDC, m_Deco.GetSize().cx * 1.4f - CameraX, 173);

	//m_Miter.Draw(m_BackDC, m_Miter.GetSize().cx * 5.0f - CameraX, 600);
	//wsprintf(miter, TEXT("   %d   "), MiterCount);
	//TextOut(m_BackDC, m_Miter.GetSize().cx * 5.4f - CameraX, 615, miter, strlen(miter));
}
