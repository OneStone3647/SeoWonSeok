#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

enum COLOR
{
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_RED,
	COLOR_BLUE
};

class Paper
{
private:
	JEngine::BitMap*	m_Paper;
	int					m_Color;

public:
	Paper();
	~Paper();

public:
	void Init(int color);

public:
	inline JEngine::BitMap* GetBitmap()
	{
		return m_Paper;
	}

	inline int GetColor()
	{
		return m_Color;
	}
};

