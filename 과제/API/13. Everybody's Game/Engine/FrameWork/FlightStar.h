#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "FlightObject.h"

enum SCORE
{
	SCORE_100,
	SCORE_1400
};

class FlightStar : public FlightObject
{
private:
	int			m_Score;

public:
	FlightStar();
	virtual ~FlightStar();

public:
	virtual void Init();

	void SetScore(int scoreIndex);

public:
	inline int GetScore()
	{
		return m_Score;
	}
};

