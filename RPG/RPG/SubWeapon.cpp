#include "SubWeapon.h"



SubWeapon::SubWeapon()
{
}


SubWeapon::~SubWeapon()
{
}

void SubWeapon::GetSubWeapon()
{
	cout << "보조 무기 : " << m_Name << " 방어력 : " << m_Def;
}

Shield::Shield()
{
	m_Name = "방패";
	m_Def = 10;
}

Dagger::Dagger()
{
	m_Name = "대거";
	m_Def = 7;
}

Glove::Glove()
{
	m_Name = "장갑";
	m_Def = 5;
}
