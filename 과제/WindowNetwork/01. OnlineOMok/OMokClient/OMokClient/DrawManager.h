#pragma once
#include "Mecro.h"
#include "Singleton.h"

class DrawManager : public Singleton<DrawManager>
{
public:
	DrawManager();
	virtual ~DrawManager();

public:
	void ErasePoint(int x, int y);
	void ReDrawPoint(int x, int y, int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void DrawBox(int Width, int Height);
	void DrawMap(int Width, int Height);

public:
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

