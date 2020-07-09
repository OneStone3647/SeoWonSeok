#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	Release();
}

void GameManager::Init(HWND hWnd, HINSTANCE hInstance)
{
	m_hWnd = hWnd;
	m_hInst = hInstance;

	// GetDC를 통해 DC를 받습니다.
	HDC hdc = GetDC(hWnd);
	// hdc와 호환되는 DC를 만듭니다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 윈도우 크기로 만듭니다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, DUBBLEBUFWIDTH, DUBBLEBUFHEIGHT);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장합니다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);
	// 사용한 DC를 해제합니다.
	ReleaseDC(hWnd, hdc);

	m_ChatBox = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY | WS_VSCROLL, WINDOWWIDTH - 260, 100, CHATWIDTH, CHATHEIGHT, m_hWnd, (HMENU)ID_CHATBOX, m_hInst, NULL);
	m_EditBox = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, WINDOWWIDTH / 2 - EDITWIDTH / 2, WINDOWHEIGHT - 100, EDITWIDTH, EDITHEIGHT, m_hWnd, (HMENU)ID_EDITBOX, m_hInst, NULL);

	m_bIsStart = false;

	m_CurColor = COLOR_BLACK;
	m_bIsSend = false;

	// 사용할 박스들을 설정합니다.
	SetBoxes();

	// 사용할 브러시와 펜을 만듭니다.
	SetTool();
}

void GameManager::Release()
{
	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어 진 DC는 DeleteDC로 지워야한다.
	DeleteDC(m_MemDC);
}

void GameManager::Update(LPARAM lParam)
{
	if (m_bIsStart == false)
	{
		DrawBackground();
		DrawPaintBox();
		DrawToolBox();
		DrawBox(m_BlackBox, m_BlackBrush, m_SelectPen);

		m_bIsStart = true;
	}

	Input(lParam);
	InputChat();
	AddStrToChat(m_ChatBox, NetManager::GetInstance()->GetInfoAnswer().answer);

	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	BitBlt(hdc, 0, 0, DUBBLEBUFWIDTH, DUBBLEBUFHEIGHT, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::DrawBackground()
{
	// 사용할 브러시와 펜을 선택하고 이전 브러시와 펜을 백업합니다.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_WhiteBrush);
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, m_LineWhitePen);

	Rectangle(m_MemDC, 0, 0, DUBBLEBUFWIDTH, DUBBLEBUFHEIGHT);

	// 백업한 이전 브러시와 펜을 불러옵니다.
	SelectObject(m_MemDC, oldBrush);
	SelectObject(m_MemDC, oldPen);
}

void GameManager::SetTool()
{
	m_BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	m_RedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_BlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	m_GreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_YellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	m_LineBlackPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	m_LineWhitePen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	m_SelectPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));
	m_BlackPen = CreatePen(PS_SOLID, 8, RGB(0, 0, 0));
	m_WhitePen = CreatePen(PS_SOLID, 12, RGB(255, 255, 255));
	m_RedPen = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));
	m_BluePen = CreatePen(PS_SOLID, 8, RGB(0, 0, 255));
	m_GreenPen = CreatePen(PS_SOLID, 8, RGB(0, 255, 0));
	m_YellowPen = CreatePen(PS_SOLID, 8, RGB(255, 255, 0));
}

void GameManager::SetBoxes()
{
	// 그림을 그리는 곳입니다.
	m_PaintBox = { PAINTBOXLEFT, PAINTBOXTOP, PAINTBOXRIGHT, PAINTBOXBOTTOM };

	// 도구를 모아둔 곳입니다.
	m_ToolBox = { TOOLBOXLEFT, TOOLBOXTOP, TOOLBOXRIGHT, TOOLBOXBOTTOM };
	// 색을 선택하는 박스입니다.
	m_BlackBox = { TOOLBOXLEFT + 20, TOOLBOXTOP + 10, TOOLBOXLEFT + 80, TOOLBOXTOP + 70 };
	m_WhiteBox = { TOOLBOXLEFT + 120, TOOLBOXTOP + 10, TOOLBOXLEFT + 180, TOOLBOXTOP + 70 };
	m_RedBox = { TOOLBOXLEFT + 220, TOOLBOXTOP + 10, TOOLBOXLEFT + 280, TOOLBOXTOP + 70 };
	m_BlueBox = { TOOLBOXLEFT + 320, TOOLBOXTOP + 10, TOOLBOXLEFT + 380, TOOLBOXTOP + 70 };
	m_GreenBox = { TOOLBOXLEFT + 420, TOOLBOXTOP + 10, TOOLBOXLEFT + 480, TOOLBOXTOP + 70 };
	m_YellowBox = { TOOLBOXLEFT + 520, TOOLBOXTOP + 10, TOOLBOXLEFT + 580, TOOLBOXTOP + 70 };
	m_ClearBox = { TOOLBOXLEFT + 620, TOOLBOXTOP + 10, TOOLBOXLEFT + 680, TOOLBOXTOP + 70 };
}

void GameManager::DrawBox(RECT rect, HBRUSH brush, HPEN pen)
{
	// 사용할 브러시와 펜을 선택하고 이전 브러시와 펜을 백업합니다.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, brush);
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, pen);

	Rectangle(m_MemDC, rect.left, rect.top, rect.right, rect.bottom);

	// 백업한 이전 브러시와 펜을 불러옵니다.
	SelectObject(m_MemDC, oldBrush);
	SelectObject(m_MemDC, oldPen);
}

void GameManager::DrawPaintBox()
{
	DrawBox(m_PaintBox, m_WhiteBrush, m_LineBlackPen);
}

void GameManager::DrawToolBox()
{
	DrawBox(m_ToolBox, m_WhiteBrush, m_LineBlackPen);
	DrawBox(m_BlackBox, m_BlackBrush, m_LineBlackPen);
	DrawBox(m_WhiteBox, m_WhiteBrush, m_LineBlackPen);
	char eraser[256] = "지우개";
	TextOut(m_MemDC, m_WhiteBox.left + 6, m_WhiteBox.top + 20, eraser, strlen(eraser));
	DrawBox(m_RedBox, m_RedBrush, m_LineBlackPen);
	DrawBox(m_BlueBox, m_BlueBrush, m_LineBlackPen);
	DrawBox(m_GreenBox, m_GreenBrush, m_LineBlackPen);
	DrawBox(m_YellowBox, m_YellowBrush, m_LineBlackPen);
	DrawBox(m_ClearBox, m_WhiteBrush, m_LineBlackPen);
	char clear[256] = "전체 지우기";
	TextOut(m_MemDC, m_ClearBox.left - 14, m_ClearBox.top + 20, clear, strlen(clear));
}

void GameManager::Input(LPARAM lParam)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_bIsSend = true;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		m_MousePoint = { LOWORD(lParam), HIWORD(lParam) };

		// 도구 상자
		if (PtInRect(&m_ToolBox, m_MousePoint))
		{
			// 페인트 상자 전체를 지웁니다.
			if (PtInRect(&m_ClearBox, m_MousePoint))
			{
				DrawPaintBox();
			}
			else
			{
				// 색을 설정합니다.
				SetColor();
			}
		}

		// 페인트 상자
		if (PtInRect(&m_PaintBox, m_MousePoint))
		{
			// 페인트 상자를 벗어나지 않게 합니다.
			if (m_MousePoint.x > PAINTBOXRIGHT - 20)
			{
				m_MousePoint.x = PAINTBOXRIGHT - 20;
			}
			if (m_MousePoint.y > PAINTBOXBOTTOM - 20)
			{
				m_MousePoint.y = PAINTBOXBOTTOM - 20;
			}
			if (m_MousePoint.x < PAINTBOXLEFT + 20)
			{
				m_MousePoint.x = PAINTBOXLEFT + 20;
			}
			if (m_MousePoint.y < PAINTBOXTOP + 20)
			{
				m_MousePoint.y = PAINTBOXTOP + 20;
			}

			if (m_CurColor != COLOR_WHITE)
			{
				// 사용할 펜을 선택하고 이전 펜을 백업합니다.
				HPEN oldPen = (HPEN)SelectObject(m_MemDC, *(GetColor(m_CurColor)));


				MoveToEx(m_MemDC, m_MousePoint.x, m_MousePoint.y, NULL);
				m_MousePoint = { LOWORD(lParam), HIWORD(lParam) };

				// 페인트 상자를 벗어나지 않게 합니다.
				if (m_MousePoint.x > PAINTBOXRIGHT - 20)
				{
					m_MousePoint.x = PAINTBOXRIGHT - 20;
				}
				if (m_MousePoint.y > PAINTBOXBOTTOM - 20)
				{
					m_MousePoint.y = PAINTBOXBOTTOM - 20;
				}
				if (m_MousePoint.x < PAINTBOXLEFT + 20)
				{
					m_MousePoint.x = PAINTBOXLEFT + 20;
				}
				if (m_MousePoint.y < PAINTBOXTOP + 20)
				{
					m_MousePoint.y = PAINTBOXTOP + 20;
				}

				LineTo(m_MemDC, m_MousePoint.x, m_MousePoint.y);

				// 백업한 이전 펜을 불러옵니다.
				SelectObject(m_MemDC, oldPen);
			}
			else
			{
				// 사용할 브러시와 펜을 선택하고 이전 브러시와 펜을 백업합니다.
				HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_WhiteBrush);
				HPEN oldPen = (HPEN)SelectObject(m_MemDC, m_WhitePen);
				m_Eraser = { m_MousePoint.x - 10, m_MousePoint.y - 10, m_MousePoint.x + 10, m_MousePoint.y + 10 };
				Rectangle(m_MemDC, m_Eraser.left, m_Eraser.top, m_Eraser.right, m_Eraser.bottom);
			}
		}
	}
}

HPEN * GameManager::GetColor(int color)
{
	switch (color)
	{
	case COLOR_BLACK:
		return &m_BlackPen;
	case COLOR_WHITE:
		return &m_WhitePen;
	case COLOR_RED:
		return &m_RedPen;
	case COLOR_BLUE:
		return &m_BluePen;
	case COLOR_GREEN:
		return &m_GreenPen;
	case COLOR_YELLOW:
		return &m_YellowPen;
	}

	return &m_BlackPen;
}

void GameManager::SetColor()
{
	if (PtInRect(&m_BlackBox, m_MousePoint))
	{
		m_CurColor = COLOR_BLACK;
		DrawToolBox();
		DrawBox(m_BlackBox, m_BlackBrush, m_SelectPen);
		return;
	}
	if (PtInRect(&m_WhiteBox, m_MousePoint))
	{
		m_CurColor = COLOR_WHITE;
		DrawToolBox();
		DrawBox(m_WhiteBox, m_WhiteBrush, m_SelectPen);
		return;
	}
	if (PtInRect(&m_RedBox, m_MousePoint))
	{
		m_CurColor = COLOR_RED;
		DrawToolBox();
		DrawBox(m_RedBox, m_RedBrush, m_SelectPen);
		return;
	}
	if (PtInRect(&m_BlueBox, m_MousePoint))
	{
		m_CurColor = COLOR_BLUE;
		DrawToolBox();
		DrawBox(m_BlueBox, m_BlueBrush, m_SelectPen);
		return;
	}
	if (PtInRect(&m_GreenBox, m_MousePoint))
	{
		m_CurColor = COLOR_GREEN;
		DrawToolBox();
		DrawBox(m_GreenBox, m_GreenBrush, m_SelectPen);
		return;
	}
	if (PtInRect(&m_YellowBox, m_MousePoint))
	{
		m_CurColor = COLOR_YELLOW;
		DrawToolBox();
		DrawBox(m_YellowBox, m_YellowBrush, m_SelectPen);
		return;
	}
}

void GameManager::InputChat()
{
	if (m_bIsSend)
	{
		char buf[BUFSIZE];
		// ID_EDITBOX에서 문자를 복사합니다.
		GetDlgItemText(m_hWnd, ID_EDITBOX, buf, sizeof(buf));

		NetManager::GetInstance()->SetAnswer(buf);
		NetManager::GetInstance()->SetAnswerInputFlag(true);

		// 전송한 문자를 삭제합니다.
		SetDlgItemText(m_hWnd, ID_EDITBOX, "");
		SetFocus(GetDlgItem(m_hWnd, ID_EDITBOX));

		m_bIsSend = false;
	}
	else
	{
		return;
	}
}

void GameManager::AddStrToChat(HWND hWnd, char * msg)
{
	if (strcmp(msg, "") != 0 && NetManager::GetInstance()->GetRecvAnswerFlag())
	{
		SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)msg);
		// 칸을 밀리게 함
		int count = (int)SendMessage(hWnd, LB_GETCOUNT, 0, 0);
		SendMessage(hWnd, LB_SETTOPINDEX, count - 1, 0);

		NetManager::GetInstance()->SetRecvAnswerFlag(false);
	}
	else
	{
		return;
	}
}
