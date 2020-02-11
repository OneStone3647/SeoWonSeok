#pragma once
#include "Mecro.h"

// 보드가 비었으면 BOARDINFO_NONE
// 검은색 피스가 있으면 BOARDINFO_BLACK
// 흰색 피스가 있으면 BOARDINFO_WHITE
enum BOARDINFO
{
	BOARDINFO_NONE = 0,
	BOARDINFO_BLACK,
	BOARDINFO_WHITE
};

class Board
{
private:
	BOARDINFO		m_BoardInfo;

public:
	Board();
	~Board();

public:
	inline BOARDINFO GetBoardInfo()
	{
		return m_BoardInfo;
	}
	inline void SetBoardInfo(BOARDINFO boardInfo)
	{
		m_BoardInfo = boardInfo;
	}
};

