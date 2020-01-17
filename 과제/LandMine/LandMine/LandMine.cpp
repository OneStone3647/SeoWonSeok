#include "LandMine.h"



LandMine::LandMine()
{
	Horizon = 5;
	Vertical = 5;
}


LandMine::~LandMine()
{
}

void LandMine::DrawMap()
{
	list<Point>::iterator iter = LandMinePoint.begin();
	for (int i = 0; i < Vertical; i++)
	{
		for (int j = 0; j < Horizon; j++)
		{
			cout << Grid[i][j];
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

	list<Point>::iterator iter;
	for (iter = LandMinePoint.begin(); iter != LandMinePoint.end(); ++iter)
	{
		Grid[(*iter).X][(*iter).Y] = 7;
	}
}

bool LandMine::SamePoint(list<Point>::iterator iter, Point point)
{
	if ((*iter).X == point.X && (*iter).Y == point.Y)
	{
		return true;
	}
	else if(LandMinePoint.size() == 1)
	{
		return false;
	}
	else
	{
		if (++iter != LandMinePoint.end())
		{
			return SamePoint(iter, point);
		}
		else
		{
			return false;
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

	list<Point>::iterator iter;
	for (int i = 0; i < Vertical; i++)
	{
		for (int j = 0; j < Horizon; j++)
		{
			int findMineCount = 0;
			// ������ ���
			if (Grid[i][j] == 7)
			{
				continue;
			}

			for (iter = SearchPoint.begin(); iter != SearchPoint.end(); ++iter)
			{
				Point tmp = { i, j };
				tmp.X += (*iter).X;
				tmp.Y += (*iter).Y;

				// �������� ��� ���
				if (tmp.X < 0 || tmp.Y < 0 || tmp.X > 4 || tmp.Y > 4)
				{
					continue;
				}

				// ���ڸ� ã�� ���
				if (Grid[tmp.X][tmp.Y] == 7)
				{
					findMineCount++;
				}
			}
			Grid[i][j] = findMineCount;
		}
	}
}
