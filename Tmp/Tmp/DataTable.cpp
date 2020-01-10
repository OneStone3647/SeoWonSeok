#include "DataTable.h"



void DataTable::Print()
{
	cout << "언어 : " << m_Kor << endl;
	cout << "수학 : " << m_Mat << endl;
	cout << "외국어 : " << m_Eng << endl;
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
