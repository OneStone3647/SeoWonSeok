#include "Data.h"



Data::Data()
{
}


Data::~Data()
{
	observerList.clear();
}

void Data::NotifyObserver()
{
	for (auto iter = observerList.begin(); iter != observerList.end(); iter++)
	{
		(*iter)->Update(m_Kor, m_Mat, m_Eng);
	}
}

void Data::AddObserver(Observer * input)
{
	observerList.push_back(input);
}

void Data::setData(int kor, int mat, int eng)
{
	m_Kor = kor;
	m_Mat = mat;
	m_Eng = eng;
}
