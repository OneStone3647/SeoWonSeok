#pragma once
class Stone
{
private:
	int m_X;
	int m_Y;

public:
	inline void Init(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}

	inline int GetX()
	{
		return m_X;
	}

	inline int GetY()
	{
		return m_Y;
	}
};