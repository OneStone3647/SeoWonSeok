#include "LandMine.h"



LandMine::LandMine()
{
	Horizon = 5;
	Vertical = 5;
}


LandMine::~LandMine()
{
}

void LandMine::SetMap()
{
	for (int i = 0; i < Vertical; i++)
	{
		for (int j = 0; j < Horizon; j++)
		{
			cout << "0";
		}
		cout << endl;
	}
	system("pause");
}

void LandMine::DrawMap()
{
	list<Point>::iterator iter = LandMinePoint.begin();
	for (int i = 0; i < Vertical; i++)
	{
		for (int j = 0; j < Horizon; j++)
		{
			Point tmp = { i, j };
			if (!SamePoint(iter, tmp))
			{
				cout << "0";
			}
			else
			{
				cout << "*";
			}
		}
		cout << endl;
	}
	system("pause");
}

void LandMine::SetLandMine()
{
	MaxLandMineCount = (int)((Horizon*Vertical)*0.2);		// �� ũ���� 20%�� ���ڷ� ����
	int tmpLandMineCount = 0;
	while (tmpLandMineCount != MaxLandMineCount)
	{
		srand((unsigned int)time(NULL));					// ���� �Լ�
		int randomX = rand() % 5;						// 0~4 ������ ����
		int randomY = rand() % 5;						// 0~4 ������ ����
		Point tmp;
		tmp.X = randomX;
		tmp.Y = randomY;

		list<Point>::iterator iter = LandMinePoint.begin();
		if (LandMinePoint.empty())
		{
			LandMinePoint.push_back(tmp);
			tmpLandMineCount++;
		}
		else if (!SamePoint(iter, tmp))
		{
			LandMinePoint.push_back(tmp);
			tmpLandMineCount++;
		}
	}
}

bool LandMine::SamePoint(list<Point>::iterator iter, Point point)
{
	if (!LandMinePoint.empty() && iter != LandMinePoint.end())
	{
		if ((*iter).X == point.X && (*iter).Y == point.Y)
		{
			return true;
		}
		else
		{
			return SamePoint(++iter, point);
		}
	}
}

void LandMine::SearchLandMine()
{
	// Ž���� ��ġ ����
	SearchPoint.push_back({ -1,-1 });
	SearchPoint.push_back({ 0,-1 });
	SearchPoint.push_back({ 1,-1 });
	SearchPoint.push_back({ -1,0 });
	SearchPoint.push_back({ 1,0 });
	SearchPoint.push_back({ -1,1 });
	SearchPoint.push_back({ 0,1 });
	SearchPoint.push_back({ 1,1 });
}
