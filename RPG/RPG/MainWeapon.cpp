#include "MainWeapon.h"



MainWeapon::MainWeapon()
{
}


MainWeapon::~MainWeapon()
{
}

void MainWeapon::GetMainWeapon()
{
	cout << "���� ���� : " << m_Name << " ���ݷ� : " << m_Att;
}

Sword::Sword()
{
	m_Name = "��";
	m_Att = 5;
}

Bow::Bow()
{
	m_Name = "Ȱ";
	m_Att = 7;
}

Staff::Staff()
{
	m_Name = "������";
	m_Att = 10;
}
