#include "DataTable.h"



void DataTable::Print()
{
	cout << "��� : " << m_Kor << endl;
	cout << "���� : " << m_Mat << endl;
	cout << "�ܱ��� : " << m_Eng << endl;
}

DataTable::DataTable()
{
}


DataTable::~DataTable()
{
}

void DataTable::Update(int kor, int mat, int eng)
{
	m_Kor = kor;
	m_Mat = mat;
	m_Eng = eng;

	Print();
}
