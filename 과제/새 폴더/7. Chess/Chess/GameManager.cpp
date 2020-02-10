#include "GameManager.h"



GameManager::GameManager()
{
	m_PlayerBlack = NULL;
	m_PlayerWhite = NULL;
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	BlockManager::GetInstance()->Init(hWnd, hInst);

	m_bFirstPlay = true;
	m_Turn = TURN_BLACK;

	if (m_PlayerBlack != NULL)
	{
		delete m_PlayerBlack;
	}
	m_PlayerBlack = new Player;
	m_PlayerBlack->Init();
	m_PlayerBlack->SetPiece(PIECECOLOR_BLACK);

	if (m_PlayerWhite != NULL)
	{
		delete m_PlayerWhite;
	}
	m_PlayerWhite = new Player;
	m_PlayerWhite->Init();
	m_PlayerWhite->SetPiece(PIECECOLOR_WHITE);
}

void GameManager::Input(LPARAM lParam)
{
	switch (m_Turn)
	{
	case TURN_BLACK:
		m_PlayerBlack->Input(lParam);
		if (m_PlayerBlack->GetState() == STATE_IDLE)
		{
			m_Turn = TURN_WHITE;
		}
		break;
	case TURN_WHITE:
		m_PlayerWhite->Input(lParam);
		if (m_PlayerWhite->GetState() == STATE_IDLE)
		{
			m_Turn = TURN_BLACK;
		}
		break;
	}
}

bool GameManager::CheckWinner(Player * player)
{
	// 말 목록에서 킹의 생존 여부를 체크한다.
	vector<Piece*> tmpPieceList = player->GetPieceList();
	vector<Piece*>::size_type i = 0;
	for (i; i < tmpPieceList.size(); ++i)
	{
		if (tmpPieceList[i]->GetPieceType() == PIECETYPE_KING && tmpPieceList[i]->GetLiveFlag() == false)
		{
			return true;
		}
	}
	return false;
}

void GameManager::Release()
{
	BlockManager::GetInstance()->Release();
	delete m_PlayerBlack;
	delete m_PlayerWhite;
}


GameManager::~GameManager()
{
}
