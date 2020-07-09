#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include <queue>
#include "Paper.h"
//#include <time.h>
//#include <stdlib.h>

class ColoredPaper : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_BackBitmap;
	JEngine::BitMap*	m_TimeBar;
	JEngine::BitMap*	m_ScoreBitmap[2];
	JEngine::BitMap*	m_TimeOverBitmap;
	JEngine::BitMap*	m_FeverBar;
	JEngine::BitMap*	m_FeverEffect;

	int				m_Score;
	bool			m_bGetScore;
	bool			m_bIsFever;
	int				m_FeverStack;
	int				m_HaveScore;

	queue<Paper*>	m_Paper;

	int				m_ElapseTime;
	int				m_Time;
	bool			m_bIsTimeOver;

public:
	ColoredPaper();
	~ColoredPaper();

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	void ClearPaper(queue<Paper*>& targetQueue);
	void SetPaper(queue<Paper*>& targetQueue);
	void CheckPaper(queue<Paper*>& targetQueue, COLOR color);
	void DrawScore();
	void DrawTimeBar();
	void DrawFeverBar();
	void SaveScore();
};

