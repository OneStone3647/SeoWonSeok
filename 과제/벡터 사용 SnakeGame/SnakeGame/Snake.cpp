#include "Snake.h"

int Point::LastX = 0;
int Point::LastY = 0;

Snake::Snake()
{
	SnakeHeadShape = "��";
	SnakeTailShape = "��";
	Head = NULL;
	bDrawState = false;
}

// ó�� ����
void Snake::SetSnake(int width, int height)
{
	Head = new Point;
	Head->Number = 0;
	Head->X = width / 2;
	if (Head->X & 2 == 1)
	{
		Head->X++;
	}
	Head->Y = height / 2;
	Head->Next = NULL;
	TailCount = 0;
	MoveSpeed = DEFAULT_MOVESPEED;
}

void Snake::ErasePoint()
{
	m_DrawManager.ErasePoint(Head->X, Head->Y);
	if (TailCount > 0)
	{
		m_DrawManager.ErasePoint(GetSnakeLastTail()->X, GetSnakeLastTail()->Y);
	}
}

void Snake::Input()
{
	char tmp;
	if (kbhit())
	{
		tmp = getch();
		if (TailCount == 0 && (tmp == KEY_UP || tmp == KEY_LEFT || tmp == KEY_DOWN || tmp == KEY_RIGHT))
		{
			key = tmp;
		}
		// ������ ���� �� �ڷ� �̵� ����
		if (TailCount > 0)
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
	CurClock = clock();
	if (CurClock - MoveClock >= MoveSpeed)
	{
		ErasePoint();
		if (TailCount > 0)
		{
			UpdateTail(Head);
		}
		switch (key)
		{
		case KEY_UP:
			if (Head->Y > 0)
			{
				// ������ ���� ���
				if (TailCount == 0)
				{
					Head->LastX = GetSnakeLastTail()->X;
					Head->LastY = GetSnakeLastTail()->Y;
				}
				else
				{
					Head->LastX = GetSnakeLastTail()->LastX;
					Head->LastY = GetSnakeLastTail()->LastY;
				}
				Head->Y--;
			}
			break;
		case KEY_LEFT:
			if (Head->X > 0)
			{
				// ������ ���� ���
				if (TailCount == 0)
				{
					Head->LastX = GetSnakeLastTail()->X;
					Head->LastY = GetSnakeLastTail()->Y;
				}
				else
				{
					Head->LastX = GetSnakeLastTail()->LastX;
					Head->LastY = GetSnakeLastTail()->LastY;
				}
				Head->X--;
			}
			break;
		case KEY_DOWN:
			if (Head->Y + 1 < y)
			{
				// ������ ���� ���
				if (TailCount == 0)
				{
					Head->LastX = GetSnakeLastTail()->X;
					Head->LastY = GetSnakeLastTail()->Y;
				}
				else
				{
					Head->LastX = GetSnakeLastTail()->LastX;
					Head->LastY = GetSnakeLastTail()->LastY;
				}
				Head->Y++;
			}
			break;
		case KEY_RIGHT:
			if (Head->X + 1 < x)
			{
				// ������ ���� ���
				if (TailCount == 0)
				{
					Head->LastX = GetSnakeLastTail()->X;
					Head->LastY = GetSnakeLastTail()->Y;
				}
				else
				{
					Head->LastX = GetSnakeLastTail()->LastX;
					Head->LastY = GetSnakeLastTail()->LastY;
				}
				Head->X++;
			}
			break;
		}
		MoveClock = CurClock;
		bDrawState = true;
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
	if (TailCount != 0)
	{
		TailCount--;
	}
}

void Snake::AddTail(Point * Node)
{
	Point* tmp;
	Point* add;
	TailCount++;
	tmp = Head;
	if (TailCount == 1)		// �� ó�� ����
	{
		add = new Point;
		add->X = tmp->LastX;
		add->Y = tmp->LastY;
		add->Next = NULL;
		add->Number = TailCount;
		tmp->Next = add;
	}
	else
	{
		while (tmp->Next != NULL)
		{
			tmp = tmp->Next;
		}
		add = new Point;
		add->X = tmp->LastX;
		add->Y = tmp->LastY;
		add->Next = NULL;
		add->Number = TailCount;
		tmp->Next = add;
	}
	IncreaseMoveSpeed();
}

void Snake::Draw()
{
	if (bDrawState)
	{
		DrawSnake(Head);
		bDrawState = false;
	}
}

void Snake::DrawSnake(Point * Node)
{
	Point* tmp = Node;
	if (tmp->Number == 0)
	{
		m_DrawManager.DrawPoint(SnakeHeadShape, Node->X, Node->Y);
	}
	if (tmp->Next == NULL)
	{
		return;
	}
	DrawSnake(Node->Next);
	m_DrawManager.DrawPoint(SnakeTailShape, Node->Next->X, Node->Next->Y);
}

// ���ڸ��� ��ǥ�� ���� ��ǥ�� �ű�
void Snake::UpdateTail(Point * Node)
{
	Point* tmp = Node;
	if (tmp->Next == NULL)
	{
		tmp->LastX = tmp->X;
		tmp->LastY = tmp->Y;
		return;
	}
	UpdateTail(Node->Next);
	Node->Next->X = tmp->X;
	Node->Next->Y = tmp->Y;
}

bool Snake::CheckWallHit()
{
	if (Head->X == 0 || Head->X == WIDTH - 1 || Head->Y == 0 || Head->Y == HEIGHT - 1)
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
	Point* tmp = Head;
	while (tmp->Next != NULL)
	{
		tmp = tmp->Next;
		// ù��°, �ι�° ���� ����
		if (TailCount > 2 && Head->X == tmp->X && Head->Y == tmp->Y)
		{
			bCheck = true;
		}
	}
	// ������ ����
	if (TailCount > 2 && tmp->Next == NULL)
	{
		if (Head->X == tmp->X && Head->Y == tmp->Y)
		{
			bCheck = true;
		}
	}
	return bCheck;
}

bool Snake::CheckBlockHit()
{
	if (m_ObjectManager.CheckBlock(Head->X, Head->Y))
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
	Point* tmp = Head;
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
