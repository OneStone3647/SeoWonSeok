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

// 게임 시작을 알리는 Flag
bool bStartGame = false;

// 처음 시작 시 카드를 2초간 보여주고 카드를 뒤집는다.
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

	// 마우스 좌표
	int Mouse_X = 0;
	int Mouse_Y = 0;

	// 윈도우 창 생성 위치 지정
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
		// 1번째 인자 : 크기를 변경할 윈도우의 핸들
		// 2, 3, 4 ,5번째 인자 : left, top, right, bottom
		// 6 번째 인자 : TRUE일 경우 윈도우가 이동된 후 WM)PAINT 메시지로 윈도우를 새로 그린다.
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