#include "CardManager.h"

CardManager* CardManager::m_This = NULL;

CardManager::CardManager()
{
	m_Card = NULL;
	m_CardList.reserve(MAXCARDLIST);				// vector 사용 메모리 예약
	bFirstPlay = true;
	srand((unsigned int)time(NULL));
}

void CardManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);									// DC를 받음

	if (m_Card != NULL)
	{
		delete[] m_Card;
	}
	m_Card = new Card[MAXCARDNUM];					// Card 클래스 배열 동적할당
	for (int i = 0; i < MAXCARDNUM; i++)
	{
		m_Card[i].Init(hdc, hInst, IDB_BITMAP1 + i);		// 각 카드들 초기화
	}

	// m_CardList 백터가 비어 있지 않을 경우 초기화
	if (!m_CardList.empty())
	{
		m_CardList.clear();
	}
	SetCardList();

	m_FirstCardListIndex = NULL;
	m_SecondCardListIndex = NULL;
	m_OpenCardCount = NULL;

	if (bFirstPlay == false)
	{
		DrawCard(hdc, Card_X, Card_Y);
		Sleep(3000);
		SetAllCardOpen(false);
		DrawCard(hdc, Card_X, Card_Y);
	}
}

// 카드리스트 작성
void CardManager::SetCardList()
{
	bool bFlag = true;
	while (bFlag)
	{
		int SameCardCount = 0;
		int RandomCardNum = (rand() % 10) + 1;		// 1~10까지의 난수 생성

		CardInfo tmpCardInfo;
		tmpCardInfo.bIsOpen = true;
		tmpCardInfo.CardNum = RandomCardNum;
		tmpCardInfo.X = 0;
		tmpCardInfo.Y = 0;

		// 초기 카드 정보 입력
		if (m_CardList.size() == 0)
		{
			m_CardList.push_back(tmpCardInfo);
		}
		else
		{
			vector<CardInfo>::size_type i = 0;
			for (i; i < m_CardList.size(); ++i)
			{
				if (m_CardList[i].CardNum == RandomCardNum)
				{
					SameCardCount++;						// 자신을 제외한 같은 카드 번호가 있을 경우 1을 증가시킨다.
				}
			}

			if (SameCardCount < 2)						// 자신을 제외한 같은 카드 번호가 2개 이하 일 경우 vector에 저장
			{
				tmpCardInfo.X = i % 5;
				tmpCardInfo.Y = i / 5;
				m_CardList.push_back(tmpCardInfo);
			}
		}

		if (m_CardList.size() == MAXCARDLIST)
		{
			bFlag = false;
		}
	}
}

void CardManager::SetCardOpen(bool bFlag, int cardNum)
{
	m_CardList[cardNum].bIsOpen = bFlag;
}

void CardManager::SetAllCardOpen(bool bFlag)
{
	for (vector<CardInfo>::size_type i = 0; i < m_CardList.size(); ++i)
	{
		SetCardOpen(bFlag, i);
	}
}

// 모든 카드를 그린다.
void CardManager::DrawCard(HDC hdc, int card_X, int card_Y)
{
	for (vector<CardInfo>::size_type i = 0; i < m_CardList.size(); ++i)
	{
		int x = i % 5;
		int y = i / 5;
		if (m_CardList[i].bIsOpen == false)
		{
			// 뒷면을 그린다.
			m_Card[10].Draw(hdc, card_X + (m_Card[10].GetCardSize().cx * x), card_Y + (m_Card[10].GetCardSize().cy * y));
		}
		else
		{
			int CardNum = m_CardList[i].CardNum - 1;
			// 앞면을 그린다.
			m_Card[CardNum].Draw(hdc, card_X + (m_Card[CardNum].GetCardSize().cx * x), card_Y + (m_Card[CardNum].GetCardSize().cy * y));
		}
	}
}

// 특정 카드를 그린다.
void CardManager::DrawCard(HDC hdc, int card_X, int card_Y, int cardNum, int x, int y)
{
	m_Card[cardNum].Draw(hdc, card_X + (m_Card[cardNum].GetCardSize().cx * x), card_Y + (m_Card[cardNum].GetCardSize().cy * y));
}

// 카드를 뒤집는 함수
void CardManager::CheckCard(HWND hWnd, HINSTANCE hInst, bool bStartGame, int mouse_X, int mouse_Y, int card_X, int card_Y)
{
	HDC hdc = GetDC(hWnd);									// DC를 받음
	int Card_Width = m_Card[10].GetCardSize().cx;
	int Card_Height = m_Card[10].GetCardSize().cy;
	// 전체 카드가 그려진 범위 내인지 확인
	if ((mouse_X >= card_X && mouse_X <= card_X + (Card_Width * 5)) && (mouse_Y >= card_Y && mouse_Y <= card_Y + (Card_Height * 4)))
	{
		int x = mouse_X / Card_Width;
		int y = mouse_Y / Card_Height;
		for (vector<CardInfo>::size_type i = 0; i < m_CardList.size(); ++i)
		{
			if (m_CardList[i].X == x && m_CardList[i].Y == y)
			{
				// 카드가 뒤집혀 있으면 앞면을 그린다.
				if (m_CardList[i].bIsOpen == false)
				{
					m_CardList[i].bIsOpen = true;
					int CardNum = m_CardList[i].CardNum - 1;
					DrawCard(hdc, card_X, card_Y, CardNum, x, y);
					// NULL을 0으로 취급하기 때문에 인덱스를 1 늘려준다.
					if (m_FirstCardListIndex == NULL)
					{
						m_FirstCardListIndex = i + 1;
					}
					else
					{
						m_SecondCardListIndex = i + 1;
					}
				}
			}
		}

		// 카드를 2개 선택 했으면
		if (m_FirstCardListIndex != NULL && m_SecondCardListIndex != NULL)
		{
			// 두 카드가 같은 디자인이면
			// NULL을 0으로 취급하기 때문에 인덱스를 1 줄여준다.
			if (m_CardList[m_FirstCardListIndex - 1].CardNum == m_CardList[m_SecondCardListIndex - 1].CardNum)
			{
				m_CardList[m_FirstCardListIndex - 1].bIsOpen = true;
				m_CardList[m_SecondCardListIndex - 1].bIsOpen = true;
				m_OpenCardCount++;
				m_FirstCardListIndex = NULL;
				m_SecondCardListIndex = NULL;
			}
			else
			{
				bStartGame = false;
				// 같은 디자인이 아닐경우 2초 뒤 카드의 뒷면을 그린다.
				Sleep(2000);
				m_CardList[m_FirstCardListIndex - 1].bIsOpen = false;
				m_CardList[m_SecondCardListIndex - 1].bIsOpen = false;
				DrawCard(hdc, card_X, card_Y, 10, m_CardList[m_FirstCardListIndex - 1].X, m_CardList[m_FirstCardListIndex - 1].Y);
				DrawCard(hdc, card_X, card_Y, 10, m_CardList[m_SecondCardListIndex - 1].X, m_CardList[m_SecondCardListIndex - 1].Y);
				m_FirstCardListIndex = NULL;
				m_SecondCardListIndex = NULL;
				bStartGame = true;
			}
		}
		CheckContinue(hWnd, hInst);
	}
}

void CardManager::CheckContinue(HWND hWnd, HINSTANCE hInst)
{
	if (m_OpenCardCount == 10)
	{
		if (MessageBox(hWnd, TEXT("계속 하시겠습니까?"), TEXT("Continue?"), MB_YESNO) == IDYES)
		{
			bFirstPlay = false;
			Init(hWnd, hInst);
		}
		else
		{
			Release();
			PostQuitMessage(0);
		}
	}
}

void CardManager::Release()
{
	delete m_This;
}


CardManager::~CardManager()
{
	delete[] m_Card;
	vector<CardInfo>().swap(m_CardList);		// swap을 사용한 vector 메모리 해제
}
