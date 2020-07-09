#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// DialogBox 프록시저
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
HWND hWnd;
LPCTSTR lpszClass = TEXT("Minesweeper");

int						g_CurSelect;
DIFFICULTY			g_Difficulty;
GameManager		g_GameManager;

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

	// 메뉴 리소스를 작성해서 윈도우 클래스에 배치
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		WindowWidth, WindowHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// 윈도우를 만들고 나면 초기화 해준다.
	g_GameManager.Init(hWnd);

	g_CurSelect = IDC_RADIO1;
	g_Difficulty = g_GameManager.GetDifficulty();

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
			g_GameManager.Update(Message.lParam);
		}
	}

	// 종료 직전에 릴리즈 해준다.
	g_GameManager.Release();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_NEW_GAME:
			g_GameManager.ResetGame();

			break;

		case ID_OPTION:
			// DialogBox 생성(인스턴, 리소스(템플리트), Dialog가 뿌려질 윈도우, DialogBox 프록시저)
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)&AboutDlgProc);

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

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND hRadio;
	int tmpSelect = NULL;

	switch (iMessage)
	{
		// DialogBox 초기화 설정
	case WM_INITDIALOG:
		tmpSelect = g_CurSelect;
		// GetDlgItem : 해당 ID의 리소스를 받아온다.
		hRadio = GetDlgItem(hDlg, g_CurSelect);
		// IDC_RADIO1을 체크된 상태로 설정한다.
		SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);

		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
			// 확인 버튼을 눌렀을 경우
		case IDOK:
			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
			{
				tmpSelect = IDC_RADIO1;
				//MessageBox(hDlg, "Easy", "초급", MB_OK);
				g_Difficulty = DIFFICULTY_EASY;
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
			{
				tmpSelect = IDC_RADIO2;
				//MessageBox(hDlg, "Normal", "중급", MB_OK);
				g_Difficulty = DIFFICULTY_NORMAL;
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
			{
				tmpSelect = IDC_RADIO3;
				//MessageBox(hDlg, "Hard", "고급", MB_OK);
				g_Difficulty = DIFFICULTY_HARD;
			}
			if (g_CurSelect != tmpSelect)
			{
				g_CurSelect = tmpSelect;
				g_GameManager.SetDifficulty(g_Difficulty);
				g_GameManager.ResetGame();
			}

			// GetDlgItem : 해당 ID의 리소스를 받아온다.
			hRadio = GetDlgItem(hDlg, g_CurSelect);
			// IDC_RADIO1을 체크된 상태로 설정한다.
			SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);

			EndDialog(hDlg, 0);

			return TRUE;

			// 취소 버튼을 눌렀을 경우
		case IDCANCEL:
			// DialogBox를 닫는다.
			EndDialog(hDlg, 0);

			return TRUE;
		}
	}

	return FALSE;
}
