#pragma once
#include "Block.h"

#define MAXPIECECOUNT 16

class Player
{
private:
	int m_X;
	int m_Y;
	Block* m_Piece;
	HWND m_hWnd;

public:
	Player();

	void Init(HWND hWnd);
	void SetPiece();
	void Input(LPARAM lParam);

	~Player();
};

