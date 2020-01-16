#include "LandMine.h"



LandMine::LandMine()
{
}


LandMine::~LandMine()
{
}

void LandMine::SetMap()
{
	cout << "===맵 크기 설정(최대 가로 : 5, 세로 : 5)===" << endl;
	cout << "가로 크기 : ";
	cin >> Horizon;
	cout << "세로 크기 :" ;
	cin >> Vertical;
	cout << endl;
	cout << "==================" << endl;

	srand((unsigned int)time(NULL));					// 랜덤 함수
	LandMineCount = (int)((Horizon*Vertical)*0.2);		// 맵 크기의 20%만 지뢰로 설정
}

void LandMine::SetLandMine()
{

}
