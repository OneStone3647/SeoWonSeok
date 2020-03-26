#include "Mecro.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// DialogBox ���Ͻ���
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
HWND hWnd;
LPCTSTR lpszClass = TEXT("BattleCity");

//int						g_CurSelect;
//DIFFICULTY			g_Difficulty;
//GameManager		g_GameManager;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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
	WndClass.lpszClassName = lpszClass;

	WndClass.lpszMenuName = NULL;

	// �޴� ���ҽ��� �ۼ��ؼ� ������ Ŭ������ ��ġ
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		600, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// �����츦 ����� ���� �ʱ�ȭ ���ش�.
	//g_GameManager.Init(hWnd);

	//g_CurSelect = IDC_RADIO1;
	//g_Difficulty = g_GameManager.GetDifficulty();

	// ������ â�� ȭ�� �߾ӿ� �����Ѵ�.
	int x, y, width, height;
	RECT rtDesk, rtWindow;
	GetWindowRect(GetDesktopWindow(), &rtDesk);
	GetWindowRect(hWnd, &rtWindow);
	width = rtWindow.right - rtWindow.left;
	height = rtWindow.bottom - rtWindow.top;
	x = (rtDesk.right - width) / 2;
	y = (rtDesk.bottom - height) / 2;
	MoveWindow(hWnd, x, y, width, height, TRUE);

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
			//g_GameManager.Update(Message.lParam);
		}
	}

	// ���� ������ ������ ���ش�.
	//g_GameManager.Release();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//switch (iMessage)
	//{
	//case WM_COMMAND:
	//	switch (LOWORD(wParam))
	//	{
	//	case ID_NEW_GAME:
	//		g_GameManager.ResetGame();

	//		break;

	//	case ID_OPTION:
	//		// DialogBox ����(�ν���, ���ҽ�(���ø�Ʈ), Dialog�� �ѷ��� ������, DialogBox ���Ͻ���)
	//		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)&AboutDlgProc);

	//		break;

	//	case ID_EXIT:
	//		PostQuitMessage(0);
	//		break;
	//	}

	//	return 0;

	//	// �����찡 �ı��Ǿ��ٴ� �޽�����.
	//case WM_DESTROY:
	//	// GetMessage�Լ��� WM_QUIT �޽����� ������.
	//	PostQuitMessage(0);

	//	return 0;
	//}

	// case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND hRadio;
	//int tmpSelect = NULL;

	//switch (iMessage)
	//{
	//	// DialogBox �ʱ�ȭ ����
	//case WM_INITDIALOG:
	//	tmpSelect = g_CurSelect;
	//	// GetDlgItem : �ش� ID�� ���ҽ��� �޾ƿ´�.
	//	hRadio = GetDlgItem(hDlg, g_CurSelect);
	//	// IDC_RADIO1�� üũ�� ���·� �����Ѵ�.
	//	SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);

	//	return TRUE;

	//case WM_COMMAND:
	//	switch (wParam)
	//	{
	//		// Ȯ�� ��ư�� ������ ���
	//	case IDOK:
	//		if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
	//		{
	//			tmpSelect = IDC_RADIO1;
	//			//MessageBox(hDlg, "Easy", "�ʱ�", MB_OK);
	//			g_Difficulty = DIFFICULTY_EASY;
	//		}
	//		else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
	//		{
	//			tmpSelect = IDC_RADIO2;
	//			//MessageBox(hDlg, "Normal", "�߱�", MB_OK);
	//			g_Difficulty = DIFFICULTY_NORMAL;
	//		}
	//		else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
	//		{
	//			tmpSelect = IDC_RADIO3;
	//			//MessageBox(hDlg, "Hard", "���", MB_OK);
	//			g_Difficulty = DIFFICULTY_HARD;
	//		}
	//		if (g_CurSelect != tmpSelect)
	//		{
	//			g_CurSelect = tmpSelect;
	//			g_GameManager.SetDifficulty(g_Difficulty);
	//			g_GameManager.ResetGame();
	//		}

	//		// GetDlgItem : �ش� ID�� ���ҽ��� �޾ƿ´�.
	//		hRadio = GetDlgItem(hDlg, g_CurSelect);
	//		// IDC_RADIO1�� üũ�� ���·� �����Ѵ�.
	//		SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);

	//		EndDialog(hDlg, 0);

	//		return TRUE;

	//		// ��� ��ư�� ������ ���
	//	case IDCANCEL:
	//		// DialogBox�� �ݴ´�.
	//		EndDialog(hDlg, 0);

	//		return TRUE;
	//	}
	//}

	return FALSE;
}