#pragma once
#include "Block.h"
#include "Collision.h"
#include "Player.h"

class Field
{
private:
	HDC			m_MemDC;

	vector<vector<Block*>> m_Block;

	Player* m_Player;

public:
	Field();
	~Field();

public:
	void Init(HDC MemDC, Player* player);
	void FileLoad(int StageIndex);
	void Update();
	void DrawBackground();
	void DrawField();
	POINT GetRandomSpawnPoint();
	Block*	SearchBlock(POINT tmpPoint);
	bool MoveableBlock();
	Block* OverlapBlock();


public:
	inline vector<vector<Block*>> GetBlock()
	{
		return m_Block;
	}
};

