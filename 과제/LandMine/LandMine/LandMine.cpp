#include "LandMine.h"



LandMine::LandMine()
{
}


LandMine::~LandMine()
{
}

void LandMine::SetMap()
{
	cout << "===�� ũ�� ����(�ִ� ���� : 5, ���� : 5)===" << endl;
	cout << "���� ũ�� : ";
	cin >> Horizon;
	cout << "���� ũ�� :" ;
	cin >> Vertical;
	cout << endl;
	cout << "==================" << endl;

	srand((unsigned int)time(NULL));					// ���� �Լ�
	LandMineCount = (int)((Horizon*Vertical)*0.2);		// �� ũ���� 20%�� ���ڷ� ����
}

void LandMine::SetLandMine()
{

}
