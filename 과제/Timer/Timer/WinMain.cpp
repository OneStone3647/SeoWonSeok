#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR IpszClass = TEXT("Timer");

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

// ���ƴٴϴ� ���� ũ��
int SE_X;
int SE_Y;

// ���ƴٴϴ� ����
int SA_Top;
int SA_Left;
int SA_Right;
int SA_Bottom;

// ���ƴٴϴ� ���� �÷���
bool bSearchFlag;

// ������ �ð� ��ġ
int DC_X;
int DC_Y;

// �Ƴ��α� �ð� ��ġ
int AC_X;
int AC_Y;

// �ʱ�ȭ �Լ�
void Init()
{
	SE_X = 100;
	SE_Y = 100;

	SA_Top = 100;
	SA_Left = 100;
	SA_Right = 400;
	SA_Bottom = 150;

	bSearchFlag = true;

	DC_X = 300;
	DC_Y = 420;

	AC_X = 200;
	AC_Y = 200;
}

// ������ ���ƴٴϴ� ��
void CALLBACK SearchEllipse(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (SE_X <= SA_Left)
	{
		bSearchFlag = true;
	}
	if (SE_X + 50 >= SA_Right)
	{
		bSearchFlag = false;
	}

	if (bSearchFlag == true)
	{
		SE_X += 10;
	}
	else
	{
		SE_X -= 10;
	}

	InvalidateRect(hWnd, NULL, TRUE);
}

// �Ƴ��α� �ð�
void CALLBACK Clock(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	// ���� �ð�
	SYSTEMTIME st;
	// �Ƴ��α� �ð� Ÿ�̸�
	static TCHAR sTime[128];

	HPEN NewPen, OldPen;

	RECT rt = { SA_Top, SA_Left, SA_Right, SA_Bottom };

	switch (iMessage)
	{
	case WM_CREATE:
		// �ʱ�ȭ
		Init();
		SetTimer(hWnd, 1, 100, SearchEllipse);
		SetTimer(hWnd, 2, 1000, Clock);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		SendMessage(hWnd, WM_TIMER, 2, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TEXT��� �߽����� �߾����� ����
		SetTextAlign(hdc, TA_CENTER);

		// ������ ���ƴٴϴ� ��
		FrameRect(hdc, &rt, CreateSolidBrush(RGB(0, 100, 244)));
		Ellipse(hdc, SE_X, SE_Y, SE_X + 50, SE_Y + 50);

		// ������ �ð�	
		GetLocalTime(&st);
		wsprintf(sTime, TEXT("%d:%d:%d"), st.wHour, st.wMinute, st.wSecond);
		TextOut(hdc, DC_X, DC_Y, sTime, lstrlen(sTime));

		// �Ƴ��α� �ð� ��ü
		Ellipse(hdc, AC_X, AC_Y, AC_X + 200, AC_Y + 200);
		// �Ƴ��α� �ð� ���� �׸���
		for (int i = 0; i < 13; i++)
		{
			wsprintf(sTime, TEXT("%d"), i);
			TextOut(hdc, int(AC_X + 100 + 100 * cos((270 + 30 * i) * 3.14 / 180)), int(AC_Y + 95 + 100 * sin((270 + 30 * i) * 3.14 / 180)), sTime, lstrlen(sTime));
		}

		// �� ħ
		NewPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		OldPen = (HPEN)SelectObject(hdc, NewPen);
		MoveToEx(hdc, AC_X + 100, AC_Y + 100, NULL);
		LineTo(hdc, int(AC_X + 100 + 55 * cos((270 + 30 * st.wHour + st.wMinute / 2) * 3.14 / 180)), int(AC_Y + 100 + 55 * sin((270 + 30 * st.wHour + st.wMinute / 2) * 3.14 / 180)));

		// �� ħ
		NewPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, NewPen);
		MoveToEx(hdc, AC_X + 100, AC_Y + 100, NULL);
		LineTo(hdc, int(AC_X + 100 + 90 * cos((270 + 6 * st.wMinute + st.wSecond / 10) * 3.14 / 180)), int(AC_Y + 100 + 90 * sin((270 + 6 * st.wMinute + st.wSecond / 10) * 3.14 / 180)));

		// �� ħ
		NewPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, NewPen);
		MoveToEx(hdc, AC_X + 100, AC_Y + 100, NULL);
		LineTo(hdc, int(AC_X + 100 + 80 * cos((270 + 6 * st.wSecond) * 3.14 / 180)), int(AC_Y + 100 + 80 * sin((270 + 6 * st.wSecond) * 3.14 / 180)));

		DeleteObject(NewPen);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}