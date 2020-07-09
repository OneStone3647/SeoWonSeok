#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Flight.h"
#include "Bullet.h"
#include "FlightStar.h"

class FightGame : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_BackBitmap;
	JEngine::BitMap*	m_TimeBar;
	JEngine::BitMap*	m_TimeOverBitmap;
	JEngine::BitMap*	m_FeverBar;
	JEngine::BitMap*	m_FeverEffect;
	JEngine::BitMap*	m_Deffence;

	int				m_Score;
	bool			m_bIsFever;
	int				m_FeverStack;

	Flight			m_Flight;

	vector<Bullet*>			m_Bullet;
	vector<FlightStar*>		m_Star;

	int				m_ElapseTime;
	int				m_Time;
	bool			m_bIsTimeOver;

	int				m_ExitTime;

	JEngine::RECT	m_Field;

	float				m_SpawnTime;
	float				m_StartSpawnTimer;
	float				m_CurSpawnTimer;

	bool			m_bHasDef;
	float			m_DefTime;
	float			m_StartDefTimer;
	float			m_CurDefTimer;

public:
	FightGame();
	~FightGame();

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	void DrawScore();
	void DrawFeverBar();
	void DrawTimeBar();
	void SaveScore();
	JEngine::POINT GetRandomPoint(FlightObject* target);
	void SpawnBullet();
	void SpawnStar();
};

