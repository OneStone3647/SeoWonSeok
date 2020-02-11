#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR IpszClass = TEXT("Chess");

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

	// 윈도우 창의 크기는 테두리와 캡션의 크기까지 합한 크기이다.
	// 작업영역의 크기를 1000x1000로 만들려면 1038x1016으로 생성해야 한다.
	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1038, 1016, NULL,
		(HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

GameManager GManager;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

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
		// 1번째 인자 : 크기를 변경할 윈도우의 핸들
		// 2, 3, 4 ,5번째 인자 : left, top, right, bottom
		// 6 번째 인자 : TRUE일 경우 윈도우가 이동된 후 WM)PAINT 메시지로 윈도우를 새로 그린다.
		MoveWindow(hWnd, x, y - 30, width - 22, height + 22, TRUE);

		GManager.Init(hWnd, g_hInst);

		return 0;
	case WM_LBUTTONDOWN:

		GManager.Input(lParam);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (GManager.GetFirstFlag())
		{
			GManager.DrawInitBoard();
		}

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		BlockManager::GetInstance()->Release();
		PostQuitMessage(0);

		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}