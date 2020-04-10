#pragma once
#include "Block.h"
#include "Collision.h"

class Field
{
private:
	HDC			m_MemDC;

	vector<vector<Block*>> m_Block;

public:
	Field();
	~Field();

public:
	void Init(HDC MemDC);
	void FileLoad(int StageIndex);
	void Update();
	void DrawBackground();
	POINT GetRandomSpawnPoint();
};

