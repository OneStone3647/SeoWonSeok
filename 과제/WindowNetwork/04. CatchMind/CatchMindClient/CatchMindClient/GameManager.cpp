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

	// GetDC�� ���� DC�� �޽��ϴ�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� ����ϴ�.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� ������ ũ��� ����ϴ�.
	m_NewBitmap = CreateCompatibleBitmap(hdc, DUBBLEBUFWIDTH, DUBBLEBUFHEIGHT);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����մϴ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);
	// ����� DC�� �����մϴ�.
	ReleaseDC(hWnd, hdc);

	m_ChatBox = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY | WS_VSCROLL, WINDOWWIDTH - 260, 100, CHATWIDTH, CHATHEIGHT, m_hWnd, (HMENU)ID_CHATBOX, m_hInst, NULL);
	m_EditBox = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, WINDOWWIDTH / 2 - EDITWIDTH / 2, WINDOWHEIGHT - 100, EDITWIDTH, EDITHEIGHT, m_hWnd, (HMENU)ID_EDITBOX, m_hInst, NULL);

	m_bIsStart = false;

	m_CurColor = COLOR_BLACK;
	m_bIsSend = false;

	// ����� �ڽ����� �����մϴ�.
	SetBoxes();

	// ����� �귯�ÿ� ���� ����ϴ�.
	SetTool();
}

void GameManager::Release()
{
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
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

	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	BitBlt(hdc, 0, 0, DUBBLEBUFWIDTH, DUBBLEBUFHEIGHT, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::DrawBackground()
{
	// ����� �귯�ÿ� ���� �����ϰ� ���� �귯�ÿ� ���� ����մϴ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_WhiteBrush);
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, m_LineWhitePen);

	Rectangle(m_MemDC, 0, 0, DUBBLEBUFWIDTH, DUBBLEBUFHEIGHT);

	// ����� ���� �귯�ÿ� ���� �ҷ��ɴϴ�.
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
	// �׸��� �׸��� ���Դϴ�.
	m_PaintBox = { PAINTBOXLEFT, PAINTBOXTOP, PAINTBOXRIGHT, PAINTBOXBOTTOM };

	// ������ ��Ƶ� ���Դϴ�.
	m_ToolBox = { TOOLBOXLEFT, TOOLBOXTOP, TOOLBOXRIGHT, TOOLBOXBOTTOM };
	// ���� �����ϴ� �ڽ��Դϴ�.
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
	// ����� �귯�ÿ� ���� �����ϰ� ���� �귯�ÿ� ���� ����մϴ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, brush);
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, pen);

	Rectangle(m_MemDC, rect.left, rect.top, rect.right, rect.bottom);

	// ����� ���� �귯�ÿ� ���� �ҷ��ɴϴ�.
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
	char eraser[256] = "���찳";
	TextOut(m_MemDC, m_WhiteBox.left + 6, m_WhiteBox.top + 20, eraser, strlen(eraser));
	DrawBox(m_RedBox, m_RedBrush, m_LineBlackPen);
	DrawBox(m_BlueBox, m_BlueBrush, m_LineBlackPen);
	DrawBox(m_GreenBox, m_GreenBrush, m_LineBlackPen);
	DrawBox(m_YellowBox, m_YellowBrush, m_LineBlackPen);
	DrawBox(m_ClearBox, m_WhiteBrush, m_LineBlackPen);
	char clear[256] = "��ü �����";
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

		// ���� ����
		if (PtInRect(&m_ToolBox, m_MousePoint))
		{
			// ����Ʈ ���� ��ü�� ����ϴ�.
			if (PtInRect(&m_ClearBox, m_MousePoint))
			{
				DrawPaintBox();
			}
			else
			{
				// ���� �����մϴ�.
				SetColor();
			}
		}

		// ����Ʈ ����
		if (PtInRect(&m_PaintBox, m_MousePoint))
		{
			// ����Ʈ ���ڸ� ����� �ʰ� �մϴ�.
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
				// ����� ���� �����ϰ� ���� ���� ����մϴ�.
				HPEN oldPen = (HPEN)SelectObject(m_MemDC, *(GetColor(m_CurColor)));


				MoveToEx(m_MemDC, m_MousePoint.x, m_MousePoint.y, NULL);
				m_MousePoint = { LOWORD(lParam), HIWORD(lParam) };

				// ����Ʈ ���ڸ� ����� �ʰ� �մϴ�.
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

				// ����� ���� ���� �ҷ��ɴϴ�.
				SelectObject(m_MemDC, oldPen);
			}
			else
			{
				// ����� �귯�ÿ� ���� �����ϰ� ���� �귯�ÿ� ���� ����մϴ�.
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
		// ID_EDITBOX���� ���ڸ� �����մϴ�.
		GetDlgItemText(m_hWnd, ID_EDITBOX, buf, sizeof(buf));

		NetManager::GetInstance()->SetAnswer(buf);
		NetManager::GetInstance()->SetAnswerInputFlag(true);

		// ������ ���ڸ� �����մϴ�.
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
		// ĭ�� �и��� ��
		int count = (int)SendMessage(hWnd, LB_GETCOUNT, 0, 0);
		SendMessage(hWnd, LB_SETTOPINDEX, count - 1, 0);

		NetManager::GetInstance()->SetRecvAnswerFlag(false);
	}
	else
	{
		return;
	}
}
