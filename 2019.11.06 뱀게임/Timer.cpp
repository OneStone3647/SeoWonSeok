#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void gotoxy(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void main()
{
	int CurClock, SecondClock, MinClock, HourClock;
	int Second = 0, Min = 0, Hour = 0;
	SecondClock = clock();
	MinClock = clock();
	HourClock = clock();
	gotoxy(10, 10);
	cout << Hour << "��";
	gotoxy(20, 10);
	cout << Second << "��";
	gotoxy(15, 10);
	cout << Min << "��";
	while (1)
	{
		CurClock = clock();
		if (CurClock - SecondClock > 16)
		{
			Second++;
			gotoxy(20, 10);
			cout << Second << "��";
			if (Second == 60)
			{
				Second = 0;
			}
			SecondClock = CurClock;
		}
		if (CurClock - MinClock > 1000)
		{
			Min++;
			gotoxy(15, 10);
			cout << Min << "��";
			if (Min == 60)
			{
				Min = 0;
			}
			MinClock = CurClock;
		}
		if (CurClock - HourClock > 60000)
		{
			Hour++;
			gotoxy(10, 10);
			cout << Hour << "��";
			if (Hour == 24)
			{
				Hour = 0;
			}
			HourClock = CurClock;
		}
	}
}