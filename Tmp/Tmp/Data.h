#pragma once
#include "Subject.h"
#include "Observer.h"
#include <vector>

using namespace std;

class Data : Subject
{
private:
	vector<Observer*> observerList;
	int m_Kor;
	int m_Mat;
	int m_Eng;
public:
	Data();
	~Data();

public:
	virtual void NotifyObserver();
	virtual void AddObserver(Observer* input);
	void setData(int kor, int mat, int eng);
};

