#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR IpszClass = TEXT("HelloWorld");

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100,100,400,300 };
	char str[] = TEXT("So Kepp your eyes on me now""������ ���� ������ �ž� ���� �� ���� Level");
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		TextOut(hdc, 200, 50, TEXT("Beautiful Korea"), 15);

		DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK | DT_VCENTER);

		// ��
		int radius = 50;
		for (int angle = 0; angle <= 360; angle++)
		{
			int x = 500;
			int y = 500;
			SetPixel(hdc, x + int(sin(angle*3.141592 / 180) * radius), y + int(cos(angle*3.141592/180) * radius), RGB(255, 0, 0));
		}

		// Ÿ��
		int radiusX = 50;
		int radiusY = 30;
		for (int angle = 0; angle <= 360; angle++)
		{
			int x = 300;
			int y = 300;
			SetPixel(hdc, x + int(sin(angle*3.141592 / 180) * radiusX), y + int(cos(angle*3.141592 / 180) * radiusY), RGB(255, 0, 0));
			radius--;
		}

		EndPaint(hWnd, &ps);
		return 0;		
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}