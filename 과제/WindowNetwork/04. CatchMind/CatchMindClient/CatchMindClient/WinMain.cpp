#include "GameManager.h"

HWND		g_hWnd;
HWND		g_LogBox;	// 로그를 표시할 창
HINSTANCE	g_hInst;		// 글로벌 인스턴스핸들값
LPCTSTR		lpszClass = TEXT("CatchMind");		// 창이름

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;
	WNDCLASS	WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체입니다.
	WndClass.cbClsExtra = 0;	// 예약영역
	WndClass.cbWndExtra = 0;	// 예약영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 아이콘 모양
	WndClass.hInstance = hInstance;		// 프로그램 핸들값(번호) 등록합니다.
	WndClass.lpfnWndProc = WndProc;		// 프로세스 함수 호출한다.
	WndClass.lpszClassName = lpszClass;		// 클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	// 윈도우의 수직과 수평이 변경되면 다시 그립니다.
	RegisterClass(&WndClass);	// 만들어진 WndClass룰 등록합니다.

	g_hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOWWIDTH, WINDOWHEIGHT, NULL,
		(HMENU)NULL, hInstance, NULL);
	if (g_hWnd == NULL)
	{
		return 1;
	}

	ShowWindow(g_hWnd, nCmdShow);
	// 무효화 영역(생성된 윈도우의 일부가 다른 윈도우 등에 가려졌거나 리사이즈 되었을 경우)을 갱신시켜주는 함수입니다.
	UpdateWindow(g_hWnd);

	// 윈도우를 만들고 나면 초기화 해준다.
	NetManager::GetInstance()->Init(g_hWnd);
	GameManager::GetInstance()->Init(g_hWnd, g_hInst);

	while (true)
	{
		// 메시지큐에 메시지가 있으면 메시지 처리합니다.
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			// 메세지가 없을때 업데이트를 진행합니다.
			GameManager::GetInstance()->Update(Message.lParam);
		}
	}

	// 종료직전에 릴리즈 해줍니다.
	NetManager::GetInstance()->DestroyInstance();
	GameManager::GetInstance()->DestroyInstance();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// 윈도우 창 생성 위치 지정합니다.
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
		// 6 번째 인자 : TRUE일 경우 윈도우가 이동된 후 WM)PAINT 메시지로 윈도우를 새로 그립니다.
		MoveWindow(hWnd, x, y - 30, width - 22, height + 22, TRUE);

		//g_LogBox = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		//	LBS_NOTIFY | WS_VSCROLL, WINDOWWIDTH - 260, 100, CHATWIDTH, CHATHEIGHT, hWnd, (HMENU)ID_CHATBOX, g_hInst, NULL);
		return 0;

		// 윈도우가 파괴되었다는 메시지입니다.
	case WM_DESTROY:
		// GetMessage함수에 WM_QUIT 메시지를 보냅니다.
		NetManager::GetInstance()->DestroyInstance();
		GameManager::GetInstance()->DestroyInstance();
		PostQuitMessage(0);

		return 0;
	}

	// case에 있는 메시지를 제외한 나머지 메시지를 처리합니다.
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
