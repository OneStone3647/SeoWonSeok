#include "Snake.h"

int Point::m_LastX = 0;
int Point::m_LastY = 0;

Snake::Snake()
{
	m_SnakeHeadShape = "��";
	m_SnakeTailShape = "��";
	m_Head = NULL;
	m_bDrawState = false;
}

// ó�� ����
void Snake::SetSnake(int width, int height)
{
	m_Head = new Point;
	m_Head->m_Number = 0;
	m_Head->m_X = width / 2;
	if (m_Head->m_X & 2 == 1)
	{
		m_Head->m_X++;
	}
	m_Head->m_Y = height / 2;
	m_Head->Next = NULL;
	m_TailCount = 0;
	m_MoveSpeed = DEFAULT_MOVESPEED;
}

void Snake::ErasePoint()
{
	m_DrawManager.ErasePoint(m_Head->m_X, m_Head->m_Y);
	if (m_TailCount > 0)
	{
		m_DrawManager.ErasePoint(GetSnakeLastTail()->m_X, GetSnakeLastTail()->m_Y);
	}
}

void Snake::Input()
{
	char tmp;
	if (kbhit())
	{
		tmp = getch();
		if (m_TailCount == 0 && (tmp == KEY_UP || tmp == KEY_LEFT || tmp == KEY_DOWN || tmp == KEY_RIGHT))
		{
			key = tmp;
		}
		// ������ ���� �� �ڷ� �̵� ����
		if (m_TailCount > 0)
		{
			switch (tmp)
			{
			case KEY_UP: 
				if (key != KEY_DOWN)
				{
					key = tmp;
				}
				break;
			case KEY_LEFT:
				if (key != KEY_RIGHT)
				{
					key = tmp;
				}
				break;
			case KEY_DOWN:
				if (key != KEY_UP)
				{
					key = tmp;
				}
				break;
			case KEY_RIGHT:
				if (key != KEY_LEFT)
				{
					key = tmp;
				}
				break;
			}
		}
	}
}

void Snake::Move(int x, int y)
{
	m_CurClock = clock();
	if (m_CurClock - m_MoveClock >= m_MoveSpeed)
	{
		ErasePoint();
		if (m_TailCount > 0)
		{
			UpdateTail(m_Head);
		}
		switch (key)
		{
		case KEY_UP:
			if (m_Head->m_Y > 0)
			{
				// ������ ���� ���
				if (m_TailCount == 0)
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_X;
					m_Head->m_LastY = GetSnakeLastTail()->m_Y;
				}
				else
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_LastX;
					m_Head->m_LastY = GetSnakeLastTail()->m_LastY;
				}
				m_Head->m_Y--;
			}
			break;
		case KEY_LEFT:
			if (m_Head->m_X > 0)
			{
				// ������ ���� ���
				if (m_TailCount == 0)
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_X;
					m_Head->m_LastY = GetSnakeLastTail()->m_Y;
				}
				else
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_LastX;
					m_Head->m_LastY = GetSnakeLastTail()->m_LastY;
				}
				m_Head->m_X--;
			}
			break;
		case KEY_DOWN:
			if (m_Head->m_Y + 1 < y)
			{
				// ������ ���� ���
				if (m_TailCount == 0)
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_X;
					m_Head->m_LastY = GetSnakeLastTail()->m_Y;
				}
				else
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_LastX;
					m_Head->m_LastY = GetSnakeLastTail()->m_LastY;
				}
				m_Head->m_Y++;
			}
			break;
		case KEY_RIGHT:
			if (m_Head->m_X + 1 < x)
			{
				// ������ ���� ���
				if (m_TailCount == 0)
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_X;
					m_Head->m_LastY = GetSnakeLastTail()->m_Y;
				}
				else
				{
					m_Head->m_LastX = GetSnakeLastTail()->m_LastX;
					m_Head->m_LastY = GetSnakeLastTail()->m_LastY;
				}
				m_Head->m_X++;
			}
			break;
		}
		m_MoveClock = m_CurClock;
		m_bDrawState = true;
	}	
}

void Snake::Release(Point * Node)
{
	if (Node == NULL)
	{
		return;
	}
	Release(Node->Next);
	delete Node;
	if (m_TailCount != 0)
	{
		m_TailCount--;
	}
}

void Snake::AddTail(Point * Node)
{
	Point* tmp;
	Point* add;
	m_TailCount++;
	tmp = m_Head;
	if (m_TailCount == 1)		// �� ó�� ����
	{
		add = new Point;
		add->m_X = tmp->m_LastX;
		add->m_Y = tmp->m_LastY;
		add->Next = NULL;
		add->m_Number = m_TailCount;
		tmp->Next = add;
	}
	else
	{
		while (tmp->Next != NULL)
		{
			tmp = tmp->Next;
		}
		add = new Point;
		add->m_X = tmp->m_LastX;
		add->m_Y = tmp->m_LastY;
		add->Next = NULL;
		add->m_Number = m_TailCount;
		tmp->Next = add;
	}
	IncreaseMoveSpeed();
}

void Snake::Draw()
{
	if (m_bDrawState)
	{
		DrawSnake(m_Head);
		m_bDrawState = false;
	}
}

void Snake::DrawSnake(Point * Node)
{
	Point* tmp = Node;
	if (tmp->m_Number == 0)
	{
		m_DrawManager.DrawPoint(m_SnakeHeadShape, Node->m_X, Node->m_Y);
	}
	if (tmp->Next == NULL)
	{
		return;
	}
	DrawSnake(Node->Next);
	m_DrawManager.DrawPoint(m_SnakeTailShape, Node->Next->m_X, Node->Next->m_Y);
}

// ���ڸ��� ��ǥ�� ���� ��ǥ�� �ű�
void Snake::UpdateTail(Point * Node)
{
	Point* tmp = Node;
	if (tmp->Next == NULL)
	{
		tmp->m_LastX = tmp->m_X;
		tmp->m_LastY = tmp->m_Y;
		return;
	}
	UpdateTail(Node->Next);
	Node->Next->m_X = tmp->m_X;
	Node->Next->m_Y = tmp->m_Y;
}

bool Snake::CheckWallHit()
{
	if (m_Head->m_X == 0 || m_Head->m_X == WIDTH - 1 || m_Head->m_Y == 0 || m_Head->m_Y == HEIGHT - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::CheckTailHit()
{
	bool bCheck = false;
	Point* tmp = m_Head;
	while (tmp->Next != NULL)
	{
		tmp = tmp->Next;
		// ù��°, �ι�° ���� ����
		if (m_TailCount > 2 && m_Head->m_X == tmp->m_X && m_Head->m_Y == tmp->m_Y)
		{
			bCheck = true;
		}
	}
	// ������ ����
	if (m_TailCount > 2 && tmp->Next == NULL)
	{
		if (m_Head->m_X == tmp->m_X && m_Head->m_Y == tmp->m_Y)
		{
			bCheck = true;
		}
	}
	return bCheck;
}

bool Snake::CheckBlockHit()
{
	if (m_ObjectManager.CheckBlock(m_Head->m_X, m_Head->m_Y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::CheckIsDead()
{
	// ���� ����� ��
 	if (CheckWallHit())
	{
		return true;
	}
	if (CheckTailHit())
	{
		return true;
	}
	return false;
}

Point * Snake::GetSnakeLastTail()
{
	Point* tmp = m_Head;
	// �Ӹ��� ���
	if (tmp->Next == NULL)
	{
		return tmp;
	}
	// ������ ���
	while (tmp->Next != NULL)
	{
		tmp = tmp->Next;
		if (tmp->Next == NULL)
		{
			return tmp;
		}
	}
	return nullptr;
}


Snake::~Snake()
{
}
