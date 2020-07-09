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

	// 마우스 관련 변수입니다.
	POINT		m_MousePoint;
	RECT		m_Eraser;
	int			m_CurColor;

	// 정답 입력 관련 변수입니다.
	bool		m_bIsSend;

	// 사용할 브러시와 펜입니다.
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

	// 그림을 그리는 곳의 RECT입니다.
	RECT		m_PaintBox;

	// 도구 상자의 RECT입니다.
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

public:	// 배경을 그리는 함수입니다.
	void DrawBackground();
	// 사용할 색의 브러시와 펜을 생성하는 함수입니다.
	void SetTool();
	// 사용되는 모든 박스의 RECT를 설정하는 함수입니다.
	void SetBoxes();
	// 박스를 그리는 함수입니다.
	void DrawBox(RECT rect, HBRUSH brush, HPEN pen);
	// 그림을 그리는 장소를 그리는 함수입니다
	void DrawPaintBox();
	// 도구 상자를 그리는 함수입니다.
	void DrawToolBox();

public:
	// 입력 관련 함수입니다.
	void Input(LPARAM lParam);
	HPEN* GetColor(int color);
	void SetColor();

public:
	void InputChat();
	void AddStrToChat(HWND hWnd, char* msg);
};

