#pragma once
class Observer
{
public:
	virtual void Update(int kor, int math, int eng) = 0;
	Observer();
	~Observer();
};

