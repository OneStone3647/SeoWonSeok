#include "DrawManager.h"



DrawManager::DrawManager()
{
}

void DrawManager::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}

void DrawManager::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void DrawManager::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
	{
		x -= str.size() / 2;
	}
	gotoxy(x, y);
	cout << str;
	return;
}

void DrawManager::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void DrawManager::DrawBox(int Width, int Height)
{
	int width = (Width * 2) + 1;
	int height = Height + 3;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", height, width);
	system(buf);

	for (int y = 0; y < Height; y++)
	{
		gotoxy(0, y);
		if (y == 0)
		{
			cout << "¢Ë";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "¢Ë";
			}
			cout << "¢Ë";
		}
		else if (y == Height - 1)
		{
			cout << "¢Ë";			
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "¢Ë";
			}
			cout << "¢Ë";
		}
		else
		{
			cout << "¢Ë";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "  ";
			}
			cout << "¢Ë";
		}
	}
	return;
}


DrawManager::~DrawManager()
{
}
