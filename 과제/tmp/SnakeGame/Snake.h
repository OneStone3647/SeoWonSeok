#pragma once
#include "Mecro.h"
#include "DrawManager.h"
#include "ObjectManager.h"

#define DEFAULT_MOVESPEED 300

enum KEY
{
	KEY_UP = 'w',
	KEY_LEFT = 'a',
	KEY_DOWN = 's',
	KEY_RIGHT = 'd',
	KEY_CONTINUE = 32
};

struct Point
{
	int m_Number;
	int m_X;
	int m_Y;
	static int m_LastX;
	static int m_LastY;
	Point* Next;
};

class Snake
{
private:
	DrawManager m_DrawManager;
	ObjectManager m_ObjectManager;
	Point* m_Head;
	string m_SnakeHeadShape;
	string m_SnakeTailShape;
	int m_CurClock;
	int m_MoveClock;
	int m_MoveSpeed;
	int m_TailCount;
	char key;
	bool m_bDrawState;
public:
	Snake();
	void SetSnake(int width, int height);
	void ErasePoint();
	void Input();
	void Move(int x, int y);
	void Release(Point* Node);
	void AddTail(Point* Node);
	void Draw();
	void DrawSnake(Point* Node);
	void UpdateTail(Point* Node);
	bool CheckWallHit();
	bool CheckTailHit();
	bool CheckBlockHit();
	bool CheckIsDead();
	Point* GetSnakeLastTail();
	inline Point* GetSnakeHead()
	{
		return m_Head;
	}
	inline int GetMoveSpeed()
	{
		return m_MoveSpeed;
	}
	inline int GetSnakeTailCount()
	{
		return m_TailCount;
	}
	inline void IncreaseMoveSpeed()
	{
		m_MoveSpeed -= 20;
	}
	~Snake();
};

