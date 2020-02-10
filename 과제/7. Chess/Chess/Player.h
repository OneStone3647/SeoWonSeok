#pragma once
#include "Piece.h"

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
	PLAYERCOLOR		m_PlayerColor;		// �÷��̾��� ��
	vector<Piece*>	m_PieceList;		// �÷��̾ ���� �ǽ��� ���
	Piece*			m_SelectPiece;		// ���� ������ �ǽ��� ����
	POINT			m_SelectPoint;		// ���콺�� ���� ������ ��ǥ
	STATE			m_State;

public:
	Player();

	void Init(PLAYERCOLOR playerColor);
	void SetPiece();

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

	inline POINT GetSelectPoint()
	{
		return m_SelectPoint;
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

