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

	DC_X = 400;
	DC_Y = 620;

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
		Ellipse(hdc, AC_X, AC_Y, AC_X + 400, AC_Y + 400);
		// �Ƴ��α� �ð� ����
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("12"), 2);
		TextOut(hdc, AC_X + 280, AC_Y + 50, TEXT("11"), 2);
		TextOut(hdc, AC_X + 330, AC_Y + 20, TEXT("10"), 2);
		TextOut(hdc, AC_X + 390, AC_Y + 25, TEXT("9"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("8"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("7"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("6"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("5"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("4"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("3"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("2"), 1);
		TextOut(hdc, AC_X + 200, AC_Y + 10, TEXT("1"), 1);

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