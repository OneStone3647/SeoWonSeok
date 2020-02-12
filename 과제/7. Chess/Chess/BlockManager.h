#pragma once
#include "Block.h"
#include "Player.h"

// 보드가 비었으면 BOARDINFO_NONE
// 검은색 피스가 있으면 BOARDINFO_BLACK
// 흰색 피스가 있으면 BOARDINFO_WHITE
enum BOARDINFO
{
	BOARDINFO_NONE = 0,
	BOARDINFO_BLACK,
	BOARDINFO_WHITE
};

struct BoardInfo
{
	BOARDINFO BoardInfo;
	POINT point;
};

class BlockManager
{
private:
	HDC				hdc;
	HINSTANCE		m_hInst;

	Block*			m_BoardBlock;
	Block*			m_BlackPieceBlock;
	Block*			m_WhitePieceBlock;

	BoardInfo*		m_BoardInfoList;

public:
	BlockManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetBoardBlock();
	void SetPieceBlock();
	void DrawAllBoard();
	void DrawPiece(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point);
	void ErasePiece(POINT point);
	void DrawInitPiece(vector<Piece*> pieceList);
	void DrawSelectBoard(POINT point);
	void EraseSelectBoard(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point);

	void InitBoardList();
	void SetBoardInPieceInit(Player* player);
	void SetBoardInfo(POINT point, BOARDINFO boardInfo);
	BoardInfo* SearchBoardInfoList(POINT point);
	void MovePieceInBoard(POINT beforePoint, POINT afterPoint, BOARDINFO boardInfo);
	bool CheckMoveInBoard(POINT currentPoint, POINT goalPoint);

	~BlockManager();

public:
	inline BoardInfo* GetBoardInfoList()
	{
		return m_BoardInfoList;
	}
};

