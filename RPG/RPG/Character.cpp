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
	cout << "�÷��̾� �̸� �Է� : ";
	cin >> Name;
	cout << "1. ���" << endl;
	cout << "2. �ü�" << endl;
	cout << "3. ������" << endl;
	cout << "���� ���� : ";
	cin >> select;
	switch (select)
	{
	case 1:
		Job = "���";
		break;
	case 2:
		Job = "�ü�";
		break;
	case 3:
		Job = "������";
		break;
	}
	Level = 1;
	Att = 5;
	MaxHP = 50;
	CurHP = MaxHP;
	MaxExp = 10;
	CurExp = 0;
}
