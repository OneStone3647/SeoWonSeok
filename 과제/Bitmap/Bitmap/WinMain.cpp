#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR IpszClass = TEXT("Bitmap");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = IpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		(HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int Card_X = 100;
int Card_Y = 100;

int Card_Width = 145;
int Card_Height = 235;

int Mouse_X = 0;
int Mouse_Y = 0;

void DrawCard(HDC hdc, HDC CardDC)
{
	HBITMAP newBitmap, oldBitmap;

	newBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	oldBitmap = (HBITMAP)SelectObject(CardDC, newBitmap);
	BitBlt(hdc, Card_X, Card_Y, Card_Width, Card_Height, CardDC, 0, 0, SRCCOPY);							// �޸�DC�� ��Ʈ���� ���� �״�� hdc�� ����Ѵ�.
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

void CheckCard(HWND hWnd)
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, CardDC;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		Mouse_X = LOWORD(lParam);
		Mouse_Y = HIWORD(lParam);
		CheckCard(hWnd);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		CardDC = CreateCompatibleDC(hdc);		// hdc�� ȣȯ�Ǵ� CardDC�� �����.

		DrawCard(hdc, CardDC);

		DeleteDC(CardDC);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}