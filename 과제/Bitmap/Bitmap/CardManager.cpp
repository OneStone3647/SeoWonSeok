#include "CardManager.h"

CardManager* CardManager::m_CManager = NULL;

CardManager::CardManager()
{
	// ī�� ���� ��ǥ
	Card_X = 100;
	Card_Y = 100;

	// ī�� ũ��
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
			// bitmap Ŭ�������� ó��
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
	// ī�尡 �׷��� ���� ���� ���
	if ((Mouse_X >= Card_X && Mouse_X <= Card_X + (Card_Width * 5)) && (Mouse_Y >= Card_Y && Mouse_Y <= Card_Y + (Card_Height) * 2))
	{
		// �� ���� ī���� ���
		if (Mouse_Y <= Card_Y + Card_Height)
		{
			if (Mouse_X >= Card_X && Mouse_X <= Card_X + Card_Width)
			{
				MessageBox(hWnd, TEXT("�� ī��� ������ ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 2))
			{
				MessageBox(hWnd, TEXT("�� ī��� ȣ���� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 3))
			{
				MessageBox(hWnd, TEXT("�� ī��� ���� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 4))
			{
				MessageBox(hWnd, TEXT("�� ī��� �ڳ��� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else
			{
				MessageBox(hWnd, TEXT("�� ī��� �� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
		}
		// �Ʒ� ���� ī���� ���
		else
		{
			if (Mouse_X >= Card_X && Mouse_X <= Card_X + Card_Width)
			{
				MessageBox(hWnd, TEXT("�� ī��� �� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 2))
			{
				MessageBox(hWnd, TEXT("�� ī��� ����� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 3))
			{
				MessageBox(hWnd, TEXT("�� ī��� ������ ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else if (Mouse_X <= Card_X + (Card_Width * 4))
			{
				MessageBox(hWnd, TEXT("�� ī��� ������ ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
			else
			{
				MessageBox(hWnd, TEXT("�� ī��� �� ī���Դϴ�."), TEXT("CheckCard"), MB_OK);
			}
		}
	}
}
