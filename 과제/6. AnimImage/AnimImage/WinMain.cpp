#include "Player.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("AnimImage");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

Player m_Player;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC MemDC;
	HBITMAP Image, OldBitmap;
	int bX, bY;
	BITMAP Bit;


	switch (iMessage)
	{
	case WM_CREATE:
		m_Player.Init(hWnd);
		return 0;
	case WM_KEYDOWN:
		m_Player.Input(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MemDC = CreateCompatibleDC(hdc);

		// 직접적으로 이미지를 로드한다.
		Image = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		// Image 선택 & 기존의 비트맵 저장
		OldBitmap = (HBITMAP)SelectObject(MemDC, Image);

		// 이미지의 정보를 가져온다.
		GetObject(Image, sizeof(BITMAP), &Bit);
		bX = Bit.bmWidth;
		bY = Bit.bmHeight;

		TransparentBlt(hdc, m_Player.GetPlayerX(), m_Player.GetPlayerY(), bX / 4, bY / 4,
			MemDC, (bX / 4) * m_Player.GetFrame(), (bY / 4) * m_Player.GetPalyerPosition(), bX / 4, bY / 4, RGB(255, 0, 255));

		SelectObject(MemDC, OldBitmap);
		DeleteObject(Image);
		DeleteDC(MemDC);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}