#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "FlightObject.h"

class Bullet : public FlightObject
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void Init();
};

