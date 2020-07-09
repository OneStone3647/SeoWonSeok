#pragma once
#include "Piece.h"
#include "Block.h"

// ���� enum
// �ڽ��� ���ʰ� ���� STATE_PLAY, �ƴ� ��� STATE_IDLE
enum STATE
{
	STATE_IDLE = 0,
	STATE_PLAY
};

enum PLAYERCOLOR
{
	PLAYERCOLOR_BLACK = 0,
	PLAYERCOLOR_WHITE
};

class Player
{
private:
	PLAYERCOLOR				m_PlayerColor;			// �÷��̾��� ��
	vector<Piece*>			m_PieceList;			// �÷��̾ ���� �ǽ��� ���
	Piece*					m_SelectPiece;			// ���� ������ �ǽ��� ����
	POINT					m_MousePoint;			// ���콺�� ��ġ ����Ʈ
	POINT					m_MousePointInBoard;	// ���忡���� ���콺�� ��ġ ����Ʈ
	STATE					m_State;

public:
	Player();

	void Init(PLAYERCOLOR playerColor);
	void SetPiece();
	void Input(LPARAM lParam);
	bool SelectPieceInPoint(POINT point);
	bool CheckPieceInPoint(POINT point);

	~Player();
	
public:
	inline	vector<Piece*> GetPieceList()
	{
		return m_PieceList;
	}

	inline Piece* GetSelectPiece()
	{
		return m_SelectPiece;
	}
	inline void SetSelectPiece(Piece* piece)
	{
		m_SelectPiece = piece;
	}

	inline POINT GetMousePoint()
	{
		return m_MousePoint;
	}

	inline POINT GetMousePointInBoard()
	{
		return m_MousePointInBoard;
	}
	inline void SetMousePointInBaord(POINT point)
	{
		m_MousePointInBoard.x = point.x / BLOCKX;
		m_MousePointInBoard.y = point.y / BLOCKY;
	}

	inline STATE GetState()
	{
		return m_State;
	}
	inline void SetState(STATE state)
	{
		m_State = state;
	}

	inline PLAYERCOLOR GetPlayerColor()
	{
		return m_PlayerColor;
	}
};

