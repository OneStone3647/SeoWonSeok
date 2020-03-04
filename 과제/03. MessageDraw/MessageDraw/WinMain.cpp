#include <windows.h>
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

// �ʱ� ��ġ ����
int mX = 100;
int mY = 100;
int kX = 500;
int kY = 500;
bool bMessageFlag = true;			// true�� ��� ���� �簢������, false�� ��� �簢���� ������
bool bRectFlag = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN newPen, oldPen;
	HBRUSH newBrush, oldBrush;

	RECT rt = { 100, 100, 400, 400 };

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		if (bMessageFlag)
		{
			if (MessageBox(hWnd, TEXT("���� �簢������ �ٲٽðڽ��ϱ�?"), TEXT("Change Ellipse to Square"), MB_YESNO) == IDYES)
			{
				bMessageFlag = false;
			}
		}
		else
		{
			if (MessageBox(hWnd, TEXT("�簢���� ������ �ٲٽðڽ��ϱ�?"), TEXT("Change Square to Ellipse"), MB_YESNO) == IDYES)
			{
				bMessageFlag = true;
			}
		}
		return 0;
	case WM_RBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("���콺�� �����̴� ������ ���ΰڽ��ϱ�?"), TEXT("Set Rect"), MB_YESNO) == IDYES)
		{
			bRectFlag = true;
		}
		else
		{
			bRectFlag = false;
		}
		return 0;
		// Ű���� ȭ��ǥ �Է�
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			kX -= 1;
			break;
		case VK_RIGHT:
			kX += 1;
			break;
		case VK_UP:
			kY -= 1;
			break;
		case VK_DOWN:
			kY += 1;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
		// ���콺 Ŀ���� ���� �ٴ�
	case WM_MOUSEMOVE:
		mX = LOWORD(lParam);
		mY = HIWORD(lParam);
		if (bRectFlag)
		{
			if (mX + 50 > 400)
			{
				mX = 350;
			}
			if (mY + 50 > 400)
			{
				mY = 350;
			}
			if (mX - 50 < 100)
			{
				mX = 150;
			}
			if (mY - 50 < 100)
			{
				mY = 150;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		FrameRect(hdc, &rt, CreateSolidBrush(RGB(0, 100, 244)));
		newPen = CreatePen(PS_SOLID, 1, RGB(125, 125, 0));
		oldPen = (HPEN)SelectObject(hdc, newPen);
		newBrush = CreateSolidBrush(RGB(0, 196, 196));
		oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
		if (bMessageFlag)
		{
			Ellipse(hdc, mX - 50, mY - 50, mX + 50, mY + 50);
			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);
			Ellipse(hdc, kX - 50, kY - 50, kX + 50, kY + 50);
		}
		else
		{
			Rectangle(hdc, mX - 50, mY - 50, mX + 50, mY + 50);
			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);
			Rectangle(hdc, kX - 50, kY - 50, kX + 50, kY + 50);
		}
		DeleteObject(newPen);
		DeleteObject(newBrush);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}