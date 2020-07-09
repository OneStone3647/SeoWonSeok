#include "GameManager.h"

HWND		g_hWnd;
HWND		g_LogBox;	// �α׸� ǥ���� â
HINSTANCE	g_hInst;		// �۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR		lpszClass = TEXT("CatchMind");		// â�̸�

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;
	WNDCLASS	WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü�Դϴ�.
	WndClass.cbClsExtra = 0;	// ���࿵��
	WndClass.cbWndExtra = 0;	// ���࿵��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������ ���
	WndClass.hInstance = hInstance;		// ���α׷� �ڵ鰪(��ȣ) ����մϴ�.
	WndClass.lpfnWndProc = WndProc;		// ���μ��� �Լ� ȣ���Ѵ�.
	WndClass.lpszClassName = lpszClass;		// Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	// �������� ������ ������ ����Ǹ� �ٽ� �׸��ϴ�.
	RegisterClass(&WndClass);	// ������� WndClass�� ����մϴ�.

	g_hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOWWIDTH, WINDOWHEIGHT, NULL,
		(HMENU)NULL, hInstance, NULL);
	if (g_hWnd == NULL)
	{
		return 1;
	}

	ShowWindow(g_hWnd, nCmdShow);
	// ��ȿȭ ����(������ �������� �Ϻΰ� �ٸ� ������ � �������ų� �������� �Ǿ��� ���)�� ���Ž����ִ� �Լ��Դϴ�.
	UpdateWindow(g_hWnd);

	// �����츦 ����� ���� �ʱ�ȭ ���ش�.
	NetManager::GetInstance()->Init(g_hWnd);
	GameManager::GetInstance()->Init(g_hWnd, g_hInst);

	while (true)
	{
		// �޽���ť�� �޽����� ������ �޽��� ó���մϴ�.
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			// �޼����� ������ ������Ʈ�� �����մϴ�.
			GameManager::GetInstance()->Update(Message.lParam);
		}
	}

	// ���������� ������ ���ݴϴ�.
	NetManager::GetInstance()->DestroyInstance();
	GameManager::GetInstance()->DestroyInstance();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// ������ â ���� ��ġ �����մϴ�.
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
		// 6 ��° ���� : TRUE�� ��� �����찡 �̵��� �� WM)PAINT �޽����� �����츦 ���� �׸��ϴ�.
		MoveWindow(hWnd, x, y - 30, width - 22, height + 22, TRUE);

		//g_LogBox = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		//	LBS_NOTIFY | WS_VSCROLL, WINDOWWIDTH - 260, 100, CHATWIDTH, CHATHEIGHT, hWnd, (HMENU)ID_CHATBOX, g_hInst, NULL);
		return 0;

		// �����찡 �ı��Ǿ��ٴ� �޽����Դϴ�.
	case WM_DESTROY:
		// GetMessage�Լ��� WM_QUIT �޽����� �����ϴ�.
		NetManager::GetInstance()->DestroyInstance();
		GameManager::GetInstance()->DestroyInstance();
		PostQuitMessage(0);

		return 0;
	}

	// case�� �ִ� �޽����� ������ ������ �޽����� ó���մϴ�.
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
