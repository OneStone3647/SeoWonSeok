#include "DrawManager.h"



DrawManager::DrawManager()
{
}


DrawManager::~DrawManager()
{
}

void DrawManager::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}

void DrawManager::ReDrawPoint(int x, int y, int Width, int Height)
{
	int newX = x * 2;
	int newY = y;
	//gotoxy(x * 2, y);
	gotoxy(newX, newY);
	if (newX == 0)
	{
		if (newY == 0)
		{
			cout << "¦£";
		}
		else if (newY == Height - 1)
		{
			cout << "¦¦";
		}
		else
		{
			cout << "¦§";
		}
	}
	else if (newX + 2 == Width * 2)
	{
		if (newY == 0)
		{
			cout << "¦¤";
		}
		else if (newY == Height - 1)
		{
			cout << "¦¥";
		}
		else
		{
			cout << "¦©";
		}
	}
	else
	{
		if (newY == 0)
		{
			cout << "¦¨";
		}
		else if (newY == Height - 1)
		{
			cout << "¦ª";
		}
		else
		{
			cout << "¦«";
		}
	}
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
	int WIDTH = (Width * 2) + 1;
	int HEIGHT = Height + 5;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", HEIGHT, WIDTH);
	system(buf);

	for (int y = 0; y < Height; y++)
	{
		gotoxy(0, y);
		if (y == 0)
		{
			cout << "¦£";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "¦¡";
			}
			cout << "¦¤";
		}
		else if (y == Height - 1)
		{
			cout << "¦¦";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "¦¡";
			}
			cout << "¦¥";
		}
		else
		{
			cout << "¦¢";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "  ";
			}
			cout << "¦¢";
		}
	}
	return;
}

void DrawManager::DrawMap(int Width, int Height)
{
	int WIDTH = (Width * 2) + 1;
	int HEIGHT = Height + 5;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", HEIGHT, WIDTH);
	system(buf);

	for (int y = 0; y < Height; y++)
	{
		gotoxy(0, y);
		if (y == 0)
		{
			cout << "¦£";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "¦¨";
			}
			cout << "¦¤";
		}
		else if (y == Height - 1)
		{
			cout << "¦¦";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "¦ª";
			}
			cout << "¦¥";
		}
		else
		{
			cout << "¦§";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦«";
			cout << "¦©";
		}
	}
	return;
}
