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
	MaxLandMineCount = (int)((Horizon*Vertical)*0.2);		// 맵 크기의 20%만 지뢰로 설정
	int tmpLandMineCount = 0;
	while (tmpLandMineCount != MaxLandMineCount)
	{
		srand((unsigned int)time(NULL));					// 랜덤 함수
		int randomX = rand() % 5;						// 0~4 범위의 난수
		int randomY = rand() % 5;						// 0~4 범위의 난수
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
	// 탐색할 위치 저장
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
			// 지뢰일 경우
			if (Grid[i][j] == 7)
			{
				continue;
			}

			for (iter = SearchPoint.begin(); iter != SearchPoint.end(); ++iter)
			{
				Point tmp = { i, j };
				tmp.X += (*iter).X;
				tmp.Y += (*iter).Y;

				// 범위에서 벗어날 경우
				if (tmp.X < 0 || tmp.Y < 0 || tmp.X > 4 || tmp.Y > 4)
				{
					continue;
				}

				// 지뢰를 찾을 경우
				if (Grid[tmp.X][tmp.Y] == 7)
				{
					findMineCount++;
				}
			}
			Grid[i][j] = findMineCount;
		}
	}
}
