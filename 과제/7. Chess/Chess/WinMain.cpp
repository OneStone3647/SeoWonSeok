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

	// ������ â�� ũ��� �׵θ��� ĸ���� ũ����� ���� ũ���̴�.
	// �۾������� ũ�⸦ 1000x1000�� ������� 1038x1016���� �����ؾ� �Ѵ�.
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
		// 1��° ���� : ũ�⸦ ������ �������� �ڵ�
		// 2, 3, 4 ,5��° ���� : left, top, right, bottom
		// 6 ��° ���� : TRUE�� ��� �����찡 �̵��� �� WM)PAINT �޽����� �����츦 ���� �׸���.
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