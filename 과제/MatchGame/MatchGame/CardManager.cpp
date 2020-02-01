#include "CardManager.h"

CardManager* CardManager::m_This = NULL;

CardManager::CardManager()
{
	m_Card = NULL;
	m_CardList.reserve(MAXCARDLIST);				// vector ��� �޸� ����
	bFirstPlay = true;
	srand((unsigned int)time(NULL));
}

void CardManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);									// DC�� ����

	if (m_Card != NULL)
	{
		delete[] m_Card;
	}
	m_Card = new Card[MAXCARDNUM];					// Card Ŭ���� �迭 �����Ҵ�
	for (int i = 0; i < MAXCARDNUM; i++)
	{
		m_Card[i].Init(hdc, hInst, IDB_BITMAP1 + i);		// �� ī��� �ʱ�ȭ
	}

	// m_CardList ���Ͱ� ��� ���� ���� ��� �ʱ�ȭ
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

// ī�帮��Ʈ �ۼ�
void CardManager::SetCardList()
{
	bool bFlag = true;
	while (bFlag)
	{
		int SameCardCount = 0;
		int RandomCardNum = (rand() % 10) + 1;		// 1~10������ ���� ����

		CardInfo tmpCardInfo;
		tmpCardInfo.bIsOpen = true;
		tmpCardInfo.CardNum = RandomCardNum;
		tmpCardInfo.X = 0;
		tmpCardInfo.Y = 0;

		// �ʱ� ī�� ���� �Է�
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
					SameCardCount++;						// �ڽ��� ������ ���� ī�� ��ȣ�� ���� ��� 1�� ������Ų��.
				}
			}

			if (SameCardCount < 2)						// �ڽ��� ������ ���� ī�� ��ȣ�� 2�� ���� �� ��� vector�� ����
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

// ��� ī�带 �׸���.
void CardManager::DrawCard(HDC hdc, int card_X, int card_Y)
{
	for (vector<CardInfo>::size_type i = 0; i < m_CardList.size(); ++i)
	{
		int x = i % 5;
		int y = i / 5;
		if (m_CardList[i].bIsOpen == false)
		{
			// �޸��� �׸���.
			m_Card[10].Draw(hdc, card_X + (m_Card[10].GetCardSize().cx * x), card_Y + (m_Card[10].GetCardSize().cy * y));
		}
		else
		{
			int CardNum = m_CardList[i].CardNum - 1;
			// �ո��� �׸���.
			m_Card[CardNum].Draw(hdc, card_X + (m_Card[CardNum].GetCardSize().cx * x), card_Y + (m_Card[CardNum].GetCardSize().cy * y));
		}
	}
}

// Ư�� ī�带 �׸���.
void CardManager::DrawCard(HDC hdc, int card_X, int card_Y, int cardNum, int x, int y)
{
	m_Card[cardNum].Draw(hdc, card_X + (m_Card[cardNum].GetCardSize().cx * x), card_Y + (m_Card[cardNum].GetCardSize().cy * y));
}

// ī�带 ������ �Լ�
void CardManager::CheckCard(HWND hWnd, HINSTANCE hInst, bool bStartGame, int mouse_X, int mouse_Y, int card_X, int card_Y)
{
	HDC hdc = GetDC(hWnd);									// DC�� ����
	int Card_Width = m_Card[10].GetCardSize().cx;
	int Card_Height = m_Card[10].GetCardSize().cy;
	// ��ü ī�尡 �׷��� ���� ������ Ȯ��
	if ((mouse_X >= card_X && mouse_X <= card_X + (Card_Width * 5)) && (mouse_Y >= card_Y && mouse_Y <= card_Y + (Card_Height * 4)))
	{
		int x = mouse_X / Card_Width;
		int y = mouse_Y / Card_Height;
		for (vector<CardInfo>::size_type i = 0; i < m_CardList.size(); ++i)
		{
			if (m_CardList[i].X == x && m_CardList[i].Y == y)
			{
				// ī�尡 ������ ������ �ո��� �׸���.
				if (m_CardList[i].bIsOpen == false)
				{
					m_CardList[i].bIsOpen = true;
					int CardNum = m_CardList[i].CardNum - 1;
					DrawCard(hdc, card_X, card_Y, CardNum, x, y);
					// NULL�� 0���� ����ϱ� ������ �ε����� 1 �÷��ش�.
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

		// ī�带 2�� ���� ������
		if (m_FirstCardListIndex != NULL && m_SecondCardListIndex != NULL)
		{
			// �� ī�尡 ���� �������̸�
			// NULL�� 0���� ����ϱ� ������ �ε����� 1 �ٿ��ش�.
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
				// ���� �������� �ƴҰ�� 2�� �� ī���� �޸��� �׸���.
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
		if (MessageBox(hWnd, TEXT("��� �Ͻðڽ��ϱ�?"), TEXT("Continue?"), MB_YESNO) == IDYES)
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
	vector<CardInfo>().swap(m_CardList);		// swap�� ����� vector �޸� ����
}
