#pragma once
#include "Mecro.h"

// ���尡 ������� BOARDINFO_NONE
// ������ �ǽ��� ������ BOARDINFO_BLACK
// ��� �ǽ��� ������ BOARDINFO_WHITE
enum BOARDINFO
{
	BOARDINFO_NONE = 0,
	BOARDINFO_BLACK,
	BOARDINFO_WHITE
};

class Board
{
private:
	RECT				m_Rect;
	BOARDINFO		m_BoardInfo;

public:
	Board();

	void Init(int x, int y);

	~Board();

public:
	inline RECT GetBoardRect()
	{
		return m_Rect;
	}

	inline BOARDINFO GetBoardInfo()
	{
		return m_BoardInfo;
	}
	inline void SetBoardInfo(BOARDINFO boardInfo)
	{
		m_BoardInfo = boardInfo;
	}
};

