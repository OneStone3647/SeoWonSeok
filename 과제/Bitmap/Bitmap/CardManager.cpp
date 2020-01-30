#include "CardManager.h"

CardManager* CardManager::m_CManager = NULL;

CardManager::CardManager()
{
	// 카드 생성 좌표
	Card_X = 100;
	Card_Y = 100;

	// 카드 크기
	Card_Width = 145;
	Card_Height = 235;
}


CardManager::~CardManager()
{
}

void CardManager::DrawCard(HINSTANCE g_hInst, HDC hdc, HDC CardDC)
{
	HBITMAP newBitmap, oldBitmap;
	Bitmap tmpBitmap;
	int BitmapCount = 0;
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 5; x++)
		{	
			// bitmap 클래스에서 처리
			//tmpBitmap.SetLoadBitmap(g_hInst, BitmapCount);
			//newBitmap = tmpBitmap.GetBitmap();
			//oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
			BitBlt(hdc, Card_X + (Card_Width * x), Card_Y + (Card_Height * y), Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
			SelectObject(CardDC, oldBitmap);
			BitmapCount++;
		}
	}
	tmpBitmap.Release();
}

void CardManager::CheckCard(HWND hWnd, int Mouse_X, int Mouse_Y)
{
	// 카드가 그려진 범위 안일 경우
	if ((Mouse_X >= Card_X && Mouse_X <= Card_X + (Card_Width * 5)) && (Mouse_Y >= Card_Y && Mouse_Y <= Card_Y + (Card_Height) * 2))
	{
		// 윗 열의 카드일 경우
		if (Mouse_Y <= Card_Y + Card_Height)
		{
			if (Mouse_X >= Card_X && Mouse_X <= Card_X + Card_Width)
			{
				MessageBox(hWnd, TEXT("이 카드는 강아지 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 2))
			{
				MessageBox(hWnd, TEXT("이 카드는 호랑이 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 3))
			{
				MessageBox(hWnd, TEXT("이 카드는 오리 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 4))
			{
				MessageBox(hWnd, TEXT("이 카드는 코끼리 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else
			{
				MessageBox(hWnd, TEXT("이 카드는 소 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
		}
		// 아랫 열의 카드일 경우
		else
		{
			if (Mouse_X >= Card_X && Mouse_X <= Card_X + Card_Width)
			{
				MessageBox(hWnd, TEXT("이 카드는 말 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 2))
			{
				MessageBox(hWnd, TEXT("이 카드는 고양이 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 3))
			{
				MessageBox(hWnd, TEXT("이 카드는 원숭이 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 4))
			{
				MessageBox(hWnd, TEXT("이 카드는 개구리 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
			else
			{
				MessageBox(hWnd, TEXT("이 카드는 닭 카드입니다."), TEXT("CheckCard"), MB_OK);
			}
		}
	}
}
