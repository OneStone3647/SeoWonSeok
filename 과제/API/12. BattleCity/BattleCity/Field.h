#pragma once
#include "Tank.h"
#include "Block.h"

class Field
{
private:
	HDC			m_MemDC;

	vector<vector<Block*>> m_Block;

	Player*				m_Player;
	vector<Enemy*>		m_Enemy;
	int						m_EnemyMaxSpawn;
	int						m_EnemySpawnCount;
	int						m_EnemyLife;

	Collision		m_FieldCollision[4];

	Bitmap		m_PlayerIcon;
	Bitmap		m_EnemyIcon;
	Bitmap		m_StageIcon;

	int				m_CurStage;
	int				m_MaxStage;
	float			m_StageTime;
	float			m_StartStageTimer;
	float			m_CurStageTimer;

	float			m_EnemySpawnTime;
	float			m_StartEnemySpawnTimer;
	float			m_CurEnemySpawnTimer;

	bool			m_bIsExit;
	bool			m_CountExit;
	float			m_ExitTime;
	float			m_StartExitTimer;
	float			m_CurExitTimer;

public:
	Field();
	~Field();

public:
	void Init(HDC MemDC);
	void FileLoad(int StageIndex);
	void Update();
	void DrawBackground();
	void DrawField();
	POINT GetRandomSpawnPoint();
	bool OverlapField(Tank* TargetTank);
	bool OverlapTank(Tank* TargetTank);
	void OverlapMissile(Tank* TargetTank);
	void ChangeBlock(Block* TargetBlock, DIRECTION Direction);
	void DrawInfo();
	void PlayerSpawn();
	void EnemySpawn();
	void SetStage(int StageIndex);
	bool DestroyedEagle();
	void IsExit();


public:
	inline vector<vector<Block*>> GetBlock()
	{
		return m_Block;
	}

	inline bool GetExitFlag()
	{
		return m_bIsExit;
	}
};

