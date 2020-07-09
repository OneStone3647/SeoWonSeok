#pragma once
#include "NetManager.h"

class GameManager : public Singleton<GameManager>
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;
	HINSTANCE	m_hInst;

	HWND	m_ChatBox;
	HWND	m_EditBox;

	bool		m_bIsStart;

	// ���콺 ���� �����Դϴ�.
	POINT		m_MousePoint;
	RECT		m_Eraser;
	int			m_CurColor;

	// ���� �Է� ���� �����Դϴ�.
	bool		m_bIsSend;

	// ����� �귯�ÿ� ���Դϴ�.
	HBRUSH	m_BlackBrush;
	HBRUSH	m_WhiteBrush;
	HBRUSH	m_RedBrush;
	HBRUSH	m_BlueBrush;
	HBRUSH	m_GreenBrush;
	HBRUSH	m_YellowBrush;
	HPEN	m_LineBlackPen;
	HPEN	m_LineWhitePen;
	HPEN	m_SelectPen;
	HPEN	m_BlackPen;
	HPEN	m_WhitePen;
	HPEN	m_RedPen;
	HPEN	m_BluePen;
	HPEN	m_GreenPen;
	HPEN	m_YellowPen;

	// �׸��� �׸��� ���� RECT�Դϴ�.
	RECT		m_PaintBox;

	// ���� ������ RECT�Դϴ�.
	RECT		m_ToolBox;
	RECT		m_BlackBox;
	RECT		m_WhiteBox;
	RECT		m_RedBox;
	RECT		m_BlueBox;
	RECT		m_GreenBox;
	RECT		m_YellowBox;
	RECT		m_ClearBox;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd, HINSTANCE hInstance);
	void Release();
	void Update(LPARAM lParam);

public:	// ����� �׸��� �Լ��Դϴ�.
	void DrawBackground();
	// ����� ���� �귯�ÿ� ���� �����ϴ� �Լ��Դϴ�.
	void SetTool();
	// ���Ǵ� ��� �ڽ��� RECT�� �����ϴ� �Լ��Դϴ�.
	void SetBoxes();
	// �ڽ��� �׸��� �Լ��Դϴ�.
	void DrawBox(RECT rect, HBRUSH brush, HPEN pen);
	// �׸��� �׸��� ��Ҹ� �׸��� �Լ��Դϴ�
	void DrawPaintBox();
	// ���� ���ڸ� �׸��� �Լ��Դϴ�.
	void DrawToolBox();

public:
	// �Է� ���� �Լ��Դϴ�.
	void Input(LPARAM lParam);
	HPEN* GetColor(int color);
	void SetColor();

public:
	void InputChat();
	void AddStrToChat(HWND hWnd, char* msg);
};

