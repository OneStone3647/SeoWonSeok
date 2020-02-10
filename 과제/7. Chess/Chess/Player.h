#pragma once
#include "Piece.h"

// 상태 enum
// 자신의 차례가 오면 STATE_PLAY, 아닐 경우 STATE_IDLE
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
	PLAYERCOLOR		m_PlayerColor;		// 플레이어의 색
	vector<Piece*>	m_PieceList;		// 플레이어가 가진 피스의 목록
	Piece*			m_SelectPiece;		// 현재 선택한 피스의 정보
	POINT			m_SelectPoint;		// 마우스로 선택 지점의 좌표
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

