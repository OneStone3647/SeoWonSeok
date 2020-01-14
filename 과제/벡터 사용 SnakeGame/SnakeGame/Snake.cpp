#include "Snake.h"

int Point::LastX = 0;
int Point::LastY = 0;

Snake::Snake()
{
	SnakeHeadShape = "⊙";
	SnakeTailShape = "○";
	Head = NULL;
	bDrawState = false;
}

// 처음 세팅
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
		// 꼬리가 생긴 후 뒤로 이동 막음
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
				// 꼬리가 없을 경우
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
				// 꼬리가 없을 경우
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
				// 꼬리가 없을 경우
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
				// 꼬리가 없을 경우
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
	if (TailCount == 1)		// 맨 처음 실행
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

// 앞자리의 좌표를 뒤의 좌표로 옮김
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
		// 첫번째, 두번째 꼬리 제외
		if (TailCount > 2 && Head->X == tmp->X && Head->Y == tmp->Y)
		{
			bCheck = true;
		}
	}
	// 마지막 꼬리
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
	// 벽에 닿았을 때
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
	// 머리일 경우
	if (tmp->Next == NULL)
	{
		return tmp;
	}
	// 꼬리일 경우
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
