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
	Card* m_Card;
	vector<CardInfo> m_CardList;
	int m_FirstCardListIndex;
	int m_SecondCardListIndex;
	int m_OpenCardCount;
	bool bFirstPlay;

public:
	CardManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetCardList();
	void SetCardOpen(bool bFlag, int cardNum);
	void SetAllCardOpen(bool bFlag);
	void DrawCard(HDC hdc, int card_X, int card_Y);
	void DrawCard(HDC hdc, int card_X, int card_Y, int cardNum, int x, int y);
	void CheckCard(HWND hWnd, HINSTANCE hInst, bool bStartGame, int mouse_X, int mouse_Y, int card_X, int card_Y);
	void CheckContinue(HWND hWnd, HINSTANCE hInst);
	void Release();

	~CardManager();
};

