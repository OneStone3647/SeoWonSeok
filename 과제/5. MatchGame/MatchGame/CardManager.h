#pragma once
#include "Card.h"
#include <vector>
#include <time.h>
#include <cstdlib>		// 난수 생성

#define MAXCARDNUM 11
#define MAXCARDLIST 20

#define Card_X 30
#define Card_Y 10

using namespace std;

struct CardInfo
{
	bool bIsOpen;		// true일 경우 카드의 그림이 출력됨
	int CardNum;		// Card 클래스 배열을 사용하여 그려낼 카드의 번호 ex) 1일 경우 IDB_BITMAP1에 해당하는 카드
	int X;
	int Y;
};

class CardManager
{
private:
	static CardManager* m_This;

public:
	static CardManager* GetInstance()
	{
		if (m_This == NULL)
		{
			m_This = new CardManager;
		}
		return m_This;
	}

private:
	HDC hdc;
	HINSTANCE m_hInst;
	Card* m_Card;
	vector<CardInfo> m_CardList;
	int m_FirstCardListIndex;
	int m_SecondCardListIndex;
	int m_OpenCardCount;
	bool m_bFirstPlay;
	bool m_bStartGame;

public:
	CardManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetCardList();
	void SetCardOpen(bool bFlag, int cardNum);
	void SetAllCardOpen(bool bFlag);
	void DrawCard(HDC hdc);
	void DrawCard(HDC hdc, int cardNum, int x, int y);
	void CheckCard(HWND hWnd, int mouse_X, int mouse_Y);
	static void CALLBACK StopClick(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	void ReturnCard(HWND hWnd);
	void CheckContinue(HWND hWnd);
	void Release();

	~CardManager();


	inline void SetStartGame(bool bFlag)
	{
		m_bStartGame = bFlag;
	}
	inline bool GetStartGame()
	{
		return m_bStartGame;
	}
};

