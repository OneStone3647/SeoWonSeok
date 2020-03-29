#include "GameManager.h"
#include "Maptool.h"

enum MODE
{
	MODE_GAME,
	MODE_MAPTOOL
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWnd;
LPCTSTR lpszClass = TEXT("BattleCity");

GameManager		g_GameManager;
Maptool				g_Maptool;
int						g_CurMode;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;

	WndClass.lpszMenuName = NULL;

	// 메뉴 리소스를 작성해서 윈도우 클래스에 배치
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		WindowWidth, WindowHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// 윈도우를 만들고 나면 초기화 해준다.
	g_Maptool.Init(hWnd);
	g_GameManager.Init(hWnd);
	g_CurMode = MODE_GAME;

	//g_CurSelect = IDC_RADIO1;
	//g_Difficulty = g_GameManager.GetDifficulty();

	while (true)
	{
		// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			// 메시지가 없을 때 업데이트를 진행한다.
			switch (g_CurMode)
			{
			case MODE_GAME:
				g_GameManager.Update();

				break;

			case MODE_MAPTOOL:
				g_Maptool.Update(Message.lParam);

				break;
			}
		}
	}

	// 종료 직전에 릴리즈 해준다.
	g_GameManager.Release();
	g_Maptool.Release();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MAIN:
			g_CurMode = MODE_GAME;
			g_GameManager.Init(hWnd);

			break;

		case ID_MAPTOOL:
			g_CurMode = MODE_MAPTOOL;
			g_Maptool.Init(hWnd);

			break;

		case ID_EXIT:
			PostQuitMessage(0);
			break;
		}

		return 0;

		// 윈도우가 파괴되었다는 메시지다.
	case WM_DESTROY:
		// GetMessage함수에 WM_QUIT 메시지를 보낸다.
		PostQuitMessage(0);

		return 0;
	}

	// case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
