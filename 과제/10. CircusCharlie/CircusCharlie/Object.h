#pragma once
#include "Bitmap.h"

class Object
{
protected:
	HDC			m_MemDC;

	RECT			m_Collision;
	RECT			m_ScoreCollision;

	float			m_X;
	float			m_Y;

	float			m_AnimTime;
	float			m_StartAnimTimer;
	float			m_CurAnimTimer;

public:
	Object();
	virtual ~Object();

public:
	virtual void Init(HDC MemDC) = 0;
	virtual void SetScoreCollision(float CameraX = 0.0f) = 0;

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline RECT GetScoreCollision()
	{
		return m_ScoreCollision;
	}
};

enum FRONTINDEX
{
	FRONTINDEX_1,
	FRONTINDEX_2
};

class Front : public Object
{
private:
	Bitmap		m_FrontBitmap[2];
	int				m_FrontIndex;

public:
	void Init(HDC MemDC);
	void Update(float* CameraX, int FieldIndex, float FieldWidth);
	void SetCollision(float CameraX = 0.0f);
	void SetScoreCollision(float CameraX = 0.0f);
};

