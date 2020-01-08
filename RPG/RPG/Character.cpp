#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}

void Character::SetPlayerInfo()
{
	int select;
	cout << "플레이어 이름 입력 : ";
	cin >> Name;
	cout << "1. 기사" << endl;
	cout << "2. 궁수" << endl;
	cout << "3. 마법사" << endl;
	cout << "직업 선택 : ";
	cin >> select;
	switch (select)
	{
	case 1:
		Job = "기사";
		break;
	case 2:
		Job = "궁수";
		break;
	case 3:
		Job = "마법사";
		break;
	}
	Level = 1;
	Att = 5;
	MaxHP = 50;
	CurHP = MaxHP;
	MaxExp = 10;
	CurExp = 0;
}
