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
	int Number;
	int X;
	int Y;
	static int LastX;
	static int LastY;
	Point* Next;
};

class Snake
{
private:
	DrawManager m_DrawManager;
	ObjectManager m_ObjectManager;
	Point* Head;
	string SnakeHeadShape;
	string SnakeTailShape;
	int CurClock;
	int MoveClock;
	int MoveSpeed;
	int TailCount;
	char key;
	bool bDrawState;
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
		return Head;
	}
	inline int GetMoveSpeed()
	{
		return MoveSpeed;
	}
	inline int GetSnakeTailCount()
	{
		return TailCount;
	}
	inline void IncreaseMoveSpeed()
	{
		MoveSpeed -= 20;
	}
	~Snake();
};

