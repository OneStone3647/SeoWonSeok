#include "DataGraph.h"



void DataGraph::Print()
{
	for (unsigned int i = 0; i < m_Kor; i++)
	{

	}
}

DataGraph::DataGraph()
{
}


DataGraph::~DataGraph()
{
}

void DataGraph::Update(int kor, int mat, int eng)
{
	m_Kor = kor;
	m_Mat = mat;
	m_Eng = eng;

	Print();
}
