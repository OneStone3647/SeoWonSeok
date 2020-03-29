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

	// �޴� ���ҽ��� �ۼ��ؼ� ������ Ŭ������ ��ġ
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		WindowWidth, WindowHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// �����츦 ����� ���� �ʱ�ȭ ���ش�.
	g_Maptool.Init(hWnd);
	g_GameManager.Init(hWnd);
	g_CurMode = MODE_GAME;

	//g_CurSelect = IDC_RADIO1;
	//g_Difficulty = g_GameManager.GetDifficulty();

	while (true)
	{
		// �޽���ť�� �޽����� ������ �޽��� ó��
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
			// �޽����� ���� �� ������Ʈ�� �����Ѵ�.
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

	// ���� ������ ������ ���ش�.
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

		// �����찡 �ı��Ǿ��ٴ� �޽�����.
	case WM_DESTROY:
		// GetMessage�Լ��� WM_QUIT �޽����� ������.
		PostQuitMessage(0);

		return 0;
	}

	// case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
