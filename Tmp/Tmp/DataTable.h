#pragma once
#include "Observer.h"
#include <iostream>

using namespace std;

class DataTable : public Observer
{
private:
	int m_Kor;
	int m_Mat;
	int m_Eng;
	void Print();

public:
	DataTable();
	~DataTable();

public:
	virtual void Update(int kor, int mat, int eng);
};

