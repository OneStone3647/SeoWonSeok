#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
	Release();
}

// �¸� �� �ٽ� �÷����ϱ� ���� �ʱ�ȭ
void Player::Init()
{
	m_X = MAPWIDTH / 2;
	if (m_X % 2 == 1)
	{
		m_X++;
	}
	m_Y = MAPHEIGHT / 2;
	
	if (!m_Stone.empty())
	{
		for (auto iter = m_Stone.begin(); iter != m_Stone.end(); ++iter)
		{
			delete *iter;
		}
		vector<Stone*>().swap(m_Stone);
	}
}

void Player::Init(int team)
{
	m_Team = team;

	if (team == PLAYER1)
	{
		m_StoneShape = "��";
		m_PlayerName = "Player1";
	}
	else
	{
		m_StoneShape = "��";
		m_PlayerName = "Player2";
	}

	Init();
}

void Player::Release()
{
	if (!m_Stone.empty())
	{
		for (auto iter = m_Stone.begin(); iter != m_Stone.end(); ++iter)
		{
			delete *iter;
		}
		vector<Stone*>().swap(m_Stone);
	}
}

void Player::PutStone()
{
	Stone* newStone = new Stone;
	newStone->Init(m_X, m_Y);
	m_Stone.push_back(newStone);
}

bool Player::SearchStone(int x, int y)
{
	for (auto iter = m_Stone.begin(); iter != m_Stone.end(); ++iter)
	{
		if ((*iter)->GetX() == x && (*iter)->GetY() == y)
		{
			return true;
		}
	}

	return false;
}

int Player::CheckNextStone(int x, int y, int addX, int addY)
{
	int count = 0;
	for (; (x >= 0 && x < MAPWIDTH) && (y >= 0 && y < MAPHEIGHT); x += addX, y += addY)
	{
		if (SearchStone(x, y))
		{
			count++;
		}
		else
		{
			break;
		}
	}

	return count;
}

// ���������� �� ���� �߽����� �ؼ� �˻縦 �Ѵ�.
bool Player::CheckVictory()
{
	int count = 0;

	// ���� �˻�
	count += CheckNextStone(m_X - 1, m_Y, -1, 0);
	count += CheckNextStone(m_X + 1, m_Y, 1, 0);
	if (count + 1 == 5)
	{
		return true;
	}

	// ���� �˻�
	count = 0;
	count += CheckNextStone(m_X, m_Y - 1, 0, -1);
	count += CheckNextStone(m_X, m_Y + 1, 0, 1);
	if (count + 1 == 5)
	{
		return true;
	}

	// ���� �밢�� �˻�
	count = 0;
	count += CheckNextStone(m_X - 1, m_Y - 1, -1, -1);
	count += CheckNextStone(m_X + 1, m_Y + 1, 1, 1);
	if (count + 1 == 5)
	{
		return true;
	}

	// ������ �밢�� �˻�
	count = 0;
	count += CheckNextStone(m_X + 1, m_Y - 1, 1, -1);
	count += CheckNextStone(m_X - 1, m_Y + 1, -1, 1);
	if (count + 1 == 5)
	{
		return true;
	}

	return false;
}
