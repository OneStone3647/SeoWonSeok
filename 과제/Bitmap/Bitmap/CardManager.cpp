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

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X, Card_Y, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);							// 메모리DC의 비트맵은 원형 그대로 hdc에 출력한다.
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + Card_Width, Card_Y, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + (Card_Width * 2), Card_Y, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + (Card_Width * 3), Card_Y, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + (Card_Width * 4), Card_Y, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X, Card_Y + Card_Height, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + Card_Width, Card_Y + Card_Height, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + (Card_Width * 2), Card_Y + Card_Height, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + (Card_Width * 3), Card_Y + Card_Height, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X + (Card_Width * 4), Card_Y + Card_Height, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);
	SelectObject(CardDC, oldBitmap);
	DeleteObject(newBitmap);
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
