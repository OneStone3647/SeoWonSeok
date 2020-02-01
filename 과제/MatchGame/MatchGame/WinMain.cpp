#include "CardManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR IpszClass = TEXT("MatchGame");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = IpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 1000, NULL,
		(HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

// ���� ������ �˸��� Flag
bool bStartGame = false;

// ó�� ���� �� ī�带 2�ʰ� �����ְ� ī�带 �����´�.
void CALLBACK SetCardBackFlag(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	CardManager::GetInstance()->SetAllCardOpen(false);
	InvalidateRect(hWnd, NULL, TRUE);
	KillTimer(hWnd, 1);
	bStartGame = true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	// ���콺 ��ǥ
	int Mouse_X = 0;
	int Mouse_Y = 0;

	// ������ â ���� ��ġ ����
	int x, y, width, height;
	RECT rtDesk, rtWindow;
	GetWindowRect(GetDesktopWindow(), &rtDesk);
	GetWindowRect(hWnd, &rtWindow);
	width = rtWindow.right - rtWindow.left;
	height = rtWindow.bottom - rtWindow.top;
	x = (rtDesk.right - width) / 2;
	y = (rtDesk.bottom - height) / 2;

	switch (iMessage)
	{
	case WM_CREATE:
		CardManager::GetInstance()->Init(hWnd, g_hInst);
		// 1��° ���� : ũ�⸦ ������ �������� �ڵ�
		// 2, 3, 4 ,5��° ���� : left, top, right, bottom
		// 6 ��° ���� : TRUE�� ��� �����찡 �̵��� �� WM)PAINT �޽����� �����츦 ���� �׸���.
		MoveWindow(hWnd, x, y, width, height, TRUE);
		SetTimer(hWnd, 1, 3000, SetCardBackFlag);
		return 0;
	case WM_LBUTTONDOWN:
		Mouse_X = LOWORD(lParam);
		Mouse_Y = HIWORD(lParam);
		if (bStartGame)
		{
			CardManager::GetInstance()->CheckCard(hWnd, g_hInst, bStartGame, Mouse_X, Mouse_Y, Card_X, Card_Y);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		CardManager::GetInstance()->DrawCard(hdc, Card_X, Card_Y);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		CardManager::GetInstance()->Release();

		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}