#include "SubWeapon.h"



SubWeapon::SubWeapon()
{
}


SubWeapon::~SubWeapon()
{
}

void SubWeapon::GetSubWeapon()
{
	cout << "���� ���� : " << m_Name << " ���� : " << m_Def;
}

Shield::Shield()
{
	m_Name = "����";
	m_Def = 10;
}

Dagger::Dagger()
{
	m_Name = "���";
	m_Def = 7;
}

Glove::Glove()
{
	m_Name = "�尩";
	m_Def = 5;
}
