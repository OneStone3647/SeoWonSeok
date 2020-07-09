#include "Field.h"



Field::Field()
{
}


Field::~Field()
{
	if (!m_Block.empty())
	{
		vector<vector<Block*>>::iterator iterY;
		vector<Block*>::iterator iterX;
		for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
		{
			for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
			{
				delete (*iterX);
			}
			iterY->clear();
			vector<Block*>().swap(*iterY);
		}
		m_Block.clear();
		vector<vector<Block*>>().swap(m_Block);
	}

	if (m_Player != NULL)
	{
		delete m_Player;
	}

	if (!m_Enemy.empty())
	{
		vector<Enemy*>::iterator iter;
		for (iter = m_Enemy.begin(); iter != m_Enemy.end(); iter++)
		{
			delete (*iter);
		}
		m_Enemy.clear();
		vector<Enemy*>().swap(m_Enemy);
	}
}

void Field::Init(HDC MemDC)
{
	m_MemDC = MemDC;

	// Block Ŭ���� ������ ���Ͱ� �̹� ������ ��� �Ҵ� �����Ѵ�.
	if (!m_Block.empty())
	{
		vector<vector<Block*>>::iterator iterY;
		vector<Block*>::iterator iterX;
		for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
		{
			for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
			{
				delete (*iterX);
			}
			iterY->clear();
			vector<Block*>().swap(*iterY);
		}
		m_Block.clear();
		vector<vector<Block*>>().swap(m_Block);
	}
	// Block Ŭ���� ������ ���� ���� �Ҵ�
	// ������ ���� ���� �޸� ũ�� ����
	m_Block.reserve(MapSizeY);
	for (int y = 0; y < MapSizeY; y++)
	{
		vector<Block*> tmpBlock;
		// ������ ���� ���� �޸� ũ�� ����
		tmpBlock.reserve(MapSizeX);
		for (int x = 0; x < MapSizeX; x++)
		{
			Block* newBlock = new Block;
			newBlock->Init(m_MemDC, (x + 1) * BlockSizeX, (y + 1) * BlockSizeY);
			tmpBlock.push_back(newBlock);
		}
		m_Block.push_back(tmpBlock);
	}

	m_CurStage = 1;
	m_MaxStage = 3;
	m_StageTime = 2000.0f;
	m_StartStageTimer = GetTickCount();
	m_CurStageTimer = 0.0f;
	FileLoad(m_CurStage);

	m_FieldCollision[0].SetCollision(BlockSizeX - 10, BlockSizeY, BlockSizeX, BlockSizeY * 16);
	m_FieldCollision[1].SetCollision(BlockSizeX * 16, BlockSizeY, BlockSizeX * 16 + 10, BlockSizeY * 16);
	m_FieldCollision[2].SetCollision(BlockSizeX, BlockSizeY - 10, BlockSizeX * 16, BlockSizeY);
	m_FieldCollision[3].SetCollision(BlockSizeX, BlockSizeY * 16, BlockSizeX * 16, BlockSizeY * 16 + 10);

	m_Player = NULL;
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(m_MemDC);
	m_Player->Spawn(GetRandomSpawnPoint());

	m_EnemyMaxSpawn = 8;
	m_EnemySpawnCount = 0;
	m_EnemyLife = 0;
	if (!m_Enemy.empty())
	{
		m_Enemy.clear();
	}
	m_Enemy.reserve(m_EnemyMaxSpawn);
	for (int i = 0; i < m_EnemyMaxSpawn; i++)
	{
		Enemy* tmpEnemy = new Enemy;
		tmpEnemy->Init(m_MemDC, i);
		if (tmpEnemy->GetAliveFlag())
		{
			m_EnemyLife++;
		}
		m_Enemy.push_back(tmpEnemy);
	}

	m_PlayerIcon.Init(m_MemDC, "Bitmap\\player_icon.bmp");
	m_EnemyIcon.Init(m_MemDC, "Bitmap\\enemy_icon.bmp");
	m_StageIcon.Init(m_MemDC, "Bitmap\\stage_icon.bmp");

	m_EnemySpawnTime = 2000.0f;
	m_StartEnemySpawnTimer = GetTickCount();
	m_CurEnemySpawnTimer = 0.0f;

	m_bIsExit = false;
	m_CountExit = false;
	m_ExitTime = 3000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;
}

void Field::FileLoad(int StageIndex)
{
	char buf[256];
	sprintf(buf, "Stage0%d.txt", StageIndex);

	HANDLE hFile = CreateFile(buf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			DWORD readB;
			int tmpInt = 0;
			ReadFile(hFile, &tmpInt, sizeof(int), &readB, NULL);
			m_Block[y][x]->SetBlockType((BLOCKTYPE)tmpInt);
		}
	}
	CloseHandle(hFile);
}

void Field::Update()
{
	DrawBackground();

	if (!m_Player->GetAliveFlag() && m_Player->GetLife() > 0)
	{
		PlayerSpawn();
	}

	m_Player->Update(!(OverlapField(m_Player) || OverlapTank(m_Player)), m_Player->GetLife() == 0 || DestroyedEagle() || m_CountExit);


	if (m_EnemySpawnCount != m_EnemyMaxSpawn)
	{
		EnemySpawn();
	}
	for (int i = 0; i < m_EnemyMaxSpawn; i++)
	{
		m_Enemy[i]->Update(!(OverlapField(m_Enemy[i]) || OverlapTank(m_Enemy[i])));
	}

	OverlapMissile(m_Player);
	for (int i = 0; i < m_EnemyMaxSpawn; i++)
	{
		OverlapMissile(m_Enemy[i]);
	}

	DrawField();
	m_Player->GetMissile()->Draw();
	for (int i = 0; i < m_EnemyMaxSpawn; i++)
	{
		m_Enemy[i]->GetMissile()->Draw();
	}

	DrawInfo();

	IsExit();

	if (m_EnemyLife == 0)
	{
		if (m_CurStage != m_MaxStage)
		{
			m_CurStage++;
			SetStage(m_CurStage);
		}
	}

}

void Field::DrawBackground()
{
	// ���ο� �귯�ø� �����Ѵ�.
	HBRUSH GrayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
	// m_MemDC�� GrayBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, GrayBrush);
	Rectangle(m_MemDC, 0, 0, GameWidth, GameHeight);

	// ���ο� �귯�ø� �����Ѵ�.
	HBRUSH BlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// m_MemDC�� BlackBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	oldBrush = (HBRUSH)SelectObject(m_MemDC, BlackBrush);
	Rectangle(m_MemDC, BlockSizeX, BlockSizeY, 16 * BlockSizeX, 16 * BlockSizeY);
	// m_MemDC�� oldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, oldBrush);

	//������ ������Ʈ�� �����Ѵ�.
	DeleteObject(GrayBrush);
	//������ ������Ʈ�� �����Ѵ�.
	DeleteObject(BlackBrush);
}

void Field::DrawField()
{
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Block[y][x]->GetBlockType() != BLOCKTYPE_EMPTY)
			{
				m_Block[y][x]->Draw();
			}
		}
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	m_FieldCollision[i].DrawCollision(m_MemDC);
	//}
}

POINT Field::GetRandomSpawnPoint()
{
	vector<POINT> newPOINT;

	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Block[y][x]->GetBlockType() == BLOCKTYPE_EMPTY)
			{
				POINT tmpPoint = m_Block[y][x]->GetBlockPoint();
				newPOINT.push_back(tmpPoint);
			}
		}
	}

	srand(time(NULL));
	int random = rand() % newPOINT.size();

	return newPOINT[random];
}

bool Field::OverlapField(Tank * TargetTank)
{
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Block[y][x]->GetBlockType() != BLOCKTYPE_EMPTY && TargetTank->GetDirectionCollision(TargetTank->GetCurDirection()).CheckOverlap(m_Block[y][x]->GetCollision().GetRect()))
			{
				return true;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (TargetTank->GetDirectionCollision(TargetTank->GetCurDirection()).CheckOverlap(m_FieldCollision[i].GetRect()))
		{
			return true;
		}
	}

	return false;
}

bool Field::OverlapTank(Tank * TargetTank)
{
	switch (TargetTank->GetTankType())
	{
	case TANKTYPE_PLAYER:
		{
			for (int i = 0; i < m_EnemySpawnCount; i++)
			{
				if (m_Enemy[i]->GetAliveFlag() 
					&& TargetTank->GetDirectionCollision(TargetTank->GetCurDirection()).CheckOverlap(m_Enemy[i]->GetMainCollision().GetRect()))
				{
					return true;
				}
			}
		}
		break;
	case TANKTYPE_ENEMY:
		{
			// �÷��̾�� ����� ���
			if (TargetTank->GetDirectionCollision(TargetTank->GetCurDirection()).CheckOverlap(m_Player->GetMainCollision().GetRect()))
			{
				return true;
			}

			// ������ ����� ���
			for (int i = 0; i < m_EnemySpawnCount; i++)
			{
				// �ڽŰ� �ٸ� ��
				if (m_Enemy[i]->GetAliveFlag() && dynamic_cast<Enemy*>(TargetTank)->GetTankNum() != m_Enemy[i]->GetTankNum())
				{
					if (TargetTank->GetDirectionCollision(TargetTank->GetCurDirection()).CheckOverlap(m_Enemy[i]->GetMainCollision().GetRect()))
					{
						return true;
					}
				}
			}
		}
		break;
	}

	return false;
}

void Field::OverlapMissile(Tank * TargetTank)
{	
	Missile* TargetMissile = TargetTank->GetMissile();
	if (TargetMissile->GetAliveFlag())
	{
		// ���� ����� ��
		for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
		{
			for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
			{
				if ((m_Block[y][x]->GetBlockType() != BLOCKTYPE_EMPTY && (m_Block[y][x]->GetBrokeType() != BROKETYPE_PASS)) && TargetMissile->GetCollision().CheckOverlap(m_Block[y][x]->GetCollision().GetRect()))
				{
					TargetMissile->SetExplosionFlag(true);

					if (m_Block[y][x]->GetBrokeType() == BROKETYPE_ABLE)
					{
						ChangeBlock(m_Block[y][x], TargetMissile->GetDirection());
					}
					return;
				}
			}
		}

		// �ʵ� �����ڸ��� ����� ��
		for (int i = 0; i < 4; i++)
		{
			if (TargetMissile->GetCollision().CheckOverlap(m_FieldCollision[i].GetRect()))
			{
				TargetMissile->SetExplosionFlag(true);
				return;
			}
		}

		// ��ũ�� ����� ��
		switch (TargetMissile->GetMissileKind())
		{
		case MISSILEKIND_PLAYER:
			{
				for (int i = 0; i < m_EnemySpawnCount; i++)
				{
					if (m_Enemy[i]->GetAliveFlag() && TargetMissile->GetCollision().CheckOverlap(m_Enemy[i]->GetMainCollision().GetRect()))
					{
						TargetMissile->SetExplosionFlag(true);
						m_Enemy[i]->GetHit();
					}
				}
			}
			break;
		case MISSILEKIND_ENEMY:
			{
				if (m_Player->GetAliveFlag() && TargetMissile->GetCollision().CheckOverlap(m_Player->GetMainCollision().GetRect()))
				{
					TargetMissile->SetExplosionFlag(true);
					m_Player->GetHit();
				}
			}
			break;
		}

		// �̻��� ���� ����� ��
		if (TargetMissile->GetMissileKind() == MISSILEKIND_PLAYER)
		{
			for (int i = 0; i < m_EnemySpawnCount; i++)
			{
				if (TargetMissile->GetAliveFlag() && TargetMissile->GetCollision().CheckOverlap(m_Enemy[i]->GetMissile()->GetCollision().GetRect()))
				{
					TargetMissile->SetExplosionFlag(true);
					m_Enemy[i]->GetMissile()->SetExplosionFlag(true);
					return;
				}
			}
		}
	}
}

void Field::ChangeBlock(Block * TargetBlock, DIRECTION Direction)
{
	if (TargetBlock->GetBlockType() == BLOCKTYPE_BLOCK13)
	{
		TargetBlock->SetBlockType(BLOCKTYPE_BLOCK14);
		return;
	}

	if (TargetBlock->GetBlockType() == BLOCKTYPE_BLOCK00)
	{
		switch (Direction)
		{
		case DIRECTION_DOWN:
			TargetBlock->SetBlockType(BLOCKTYPE_BLOCK03);
			break;
		case DIRECTION_LEFT:
			TargetBlock->SetBlockType(BLOCKTYPE_BLOCK02);
			break;
		case DIRECTION_RIGHT:
			TargetBlock->SetBlockType(BLOCKTYPE_BLOCK04);
			break;
		case DIRECTION_UP:
			TargetBlock->SetBlockType(BLOCKTYPE_BLOCK01);
			break;
		}
	}
	else
	{
		TargetBlock->SetBlockType(BLOCKTYPE_EMPTY);
	}
}

void Field::DrawInfo()
{
	// ���ο� �귯�ø� �����Ѵ�.
	HBRUSH GrayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
	// m_MemDC�� GrayBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, GrayBrush);

	HPEN GrayPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, GrayPen);

	// EnemyIcon ���
	Rectangle(m_MemDC, 1080, 100, 1160, 250);
	// PlayerIcon ���
	Rectangle(m_MemDC, 1080, 500, 1160, 550);
	// Stage ���
	Rectangle(m_MemDC, 1080, 700, 1160, 820);

	// m_MemDC�� oldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, oldBrush);
	// m_MemDC�� oldPen�� �����Ѵ�.
	SelectObject(m_MemDC, oldPen);

	//������ ������Ʈ�� �����Ѵ�.
	DeleteObject(GrayBrush);
	DeleteObject(GrayPen);

	int tmpCount = 0;
	for (int i = 0; i < m_EnemyMaxSpawn; i++)
	{
		if (m_Enemy[i]->GetAliveFlag())
		{
			tmpCount++;
		}
	}
	m_EnemyLife = tmpCount;

	int y = 0;
	for (int i = 0; i < m_EnemyLife; i++)
	{
		m_EnemyIcon.Draw(m_MemDC, 1080 + 40 * (i % 2), 100 + 40 * y, 2.0f);
		if (i % 2 == 1)
		{
			y++;
		}
	}

	m_PlayerIcon.Draw(m_MemDC, 1080, 500, 2.0f);
	TCHAR life[128];
	wsprintf(life, TEXT("%d"), m_Player->GetLife());
	TextOut(m_MemDC, 1120, 500, life, strlen(life));

	m_StageIcon.Draw(m_MemDC, 1080, 700, 2.0f);
	TCHAR stage[128];
	wsprintf(stage, TEXT("%d"), m_CurStage);
	TextOut(m_MemDC, 1140, 740, stage, strlen(stage));

	SetTextAlign(m_MemDC, TA_CENTER);
	if (m_Player->GetLife() == 0 || DestroyedEagle())
	{
		TextOut(m_MemDC, GameWidth / 2, GameHeight / 2, "  LOSE...   ", strlen("  LOSE...   "));
	}
	if (m_EnemyLife == 0)
	{
		TextOut(m_MemDC, GameWidth / 2, GameHeight / 2, "  WIN !!  ", strlen("  WIN !!  "));
	}
}

void Field::PlayerSpawn()
{
	while (true)
	{
		POINT RandomPoint = GetRandomSpawnPoint();
		int OverlapCheck = 0;

		for (int i = 0; i < m_EnemySpawnCount; i++)
		{
			if (!m_Enemy[i]->GetMainCollision().CheckOverlapPoint(RandomPoint))
			{
				OverlapCheck++;
			}
		}

		if (OverlapCheck == m_EnemySpawnCount)
		{
			m_Player->Spawn(GetRandomSpawnPoint());
			return;
		}
	}
}

void Field::EnemySpawn()
{
	m_CurEnemySpawnTimer = GetTickCount();

	if (m_EnemySpawnCount == 1)
	{
		m_EnemySpawnTime = 4000.0f;
	}

	if (m_CurEnemySpawnTimer - m_StartEnemySpawnTimer >= m_EnemySpawnTime)
	{
		while (true)
		{
			POINT RandomPoint = GetRandomSpawnPoint();
			int OverlapCheck = 0;
			if (m_EnemySpawnCount == 0)
			{
				if (!m_Player->GetMainCollision().CheckOverlapPoint(RandomPoint))
				{
					m_Enemy[0]->Spawn(RandomPoint);
					break;
				}
			}
			else
			{
				for (int i = 0; i < m_EnemySpawnCount; i++)
				{
					if (!m_Enemy[i]->GetMainCollision().CheckOverlapPoint(RandomPoint))
					{
						OverlapCheck++;
					}
				}
			}

			if (OverlapCheck == m_EnemySpawnCount && !m_Player->GetMainCollision().CheckOverlapPoint(RandomPoint))
			{
				m_Enemy[m_EnemySpawnCount]->Spawn(RandomPoint);
				break;
			}
		}

		m_EnemySpawnCount++;
		m_StartEnemySpawnTimer = m_CurEnemySpawnTimer;
	}
}

void Field::SetStage(int StageIndex)
{
	FileLoad(StageIndex);
	PlayerSpawn();
	for (int i = 0; i < m_EnemyMaxSpawn; i++)
	{
		m_StartEnemySpawnTimer = GetTickCount();
		m_Enemy[i]->SetSpawnFlag(false);
		m_Enemy[i]->SetAliveFlag(true);
	}
	m_EnemySpawnCount = 0;

	m_StageTime = 2000.0f;
	m_StartStageTimer = GetTickCount();
	m_CurStageTimer = 0.0f;
}

bool Field::DestroyedEagle()
{
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Block[y][x]->GetBlockType() == BLOCKTYPE_BLOCK14)
			{
				return true;
			}
		}
	}

	return false;
}

void Field::IsExit()
{
	if (m_Player->GetLife() == 0 || DestroyedEagle())
	{
		if (!m_CountExit)
		{
			m_StartExitTimer = GetTickCount();
		}
		m_CountExit = true;
	}

	if (m_EnemyLife == 0 && m_CurStage == m_MaxStage)
	{
		if (!m_CountExit)
		{
			m_StartExitTimer = GetTickCount();
		}
		m_CountExit = true;
	}

	m_CurExitTimer = GetTickCount();
	if (m_CountExit && m_CurExitTimer - m_StartExitTimer >= m_ExitTime)
	{
		m_bIsExit = true;
	}
}
