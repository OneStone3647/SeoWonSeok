#pragma once
#include "Observer.h"

class Subject
{
public:
	Subject();
	~Subject();

public:
	virtual void NotifyObserver() = 0;
	virtual void AddObserver(Observer* input) = 0;
};

