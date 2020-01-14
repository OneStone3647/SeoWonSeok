#pragma once
#include "Mecro.h"

class DrawManager
{
public:
	DrawManager();
	~DrawManager();

public:
	void EreasePoint(int x, int y);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void DrawBox(int Width, int Height);
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

