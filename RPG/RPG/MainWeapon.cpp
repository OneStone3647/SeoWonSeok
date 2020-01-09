#include "MainWeapon.h"



MainWeapon::MainWeapon()
{
}


MainWeapon::~MainWeapon()
{
}

void MainWeapon::GetMainWeapon()
{
	cout << "메인 무기 : " << m_Name << " 공격력 : " << m_Att;
}

Sword::Sword()
{
	m_Name = "검";
	m_Att = 5;
}

Bow::Bow()
{
	m_Name = "활";
	m_Att = 7;
}

Staff::Staff()
{
	m_Name = "스태프";
	m_Att = 10;
}
