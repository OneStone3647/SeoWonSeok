#include "Field.h"



Field::Field()
{
}


Field::~Field()
{
}

void Field::Init(HDC MemDC, Player * player)
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
	FileLoad(1);

	m_Player = player;
	m_Player->Spawn(GetRandomSpawnPoint());
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

	m_Player->Update(MoveableBlock());

	DrawField();
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

	int random = rand() % newPOINT.size();

	return newPOINT[random];
}

Block * Field::SearchBlock(POINT tmpPoint)
{
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if ((m_Block[y][x]->GetBlockPoint().x / BlockSizeX == tmpPoint.x) && (m_Block[y][x]->GetBlockPoint().y / BlockSizeY == tmpPoint.y))
			{
				return m_Block[y][x];
			}
		}
	}

	return nullptr;
}

bool Field::MoveableBlock()
{
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Player->GetCollision().CheckOverlap(m_Block[y][x]->GetCollision().GetCollision()))
			{
				if (m_Block[y][x]->GetWalkable() == WALKABLE_ABLE)
				{
					return true;
				}
				else
				{
					if (m_Player->GetCollision().GetCollision().left<m_Block[y][x]->GetCollision().GetCollision().right&&
						m_Player->GetCollision().GetCollision().right > m_Block[y][x]->GetCollision().GetCollision().left&&
						m_Player->GetCollision().GetCollision().top < m_Block[y][x]->GetCollision().GetCollision().bottom&&
						m_Player->GetCollision().GetCollision().bottom > m_Block[y][x]->GetCollision().GetCollision().top)
					{
						return false;
					}
					return true;
				}
			}
		}
	}

	return true;
}

Block * Field::OverlapBlock()
{
	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Player->GetCollision().CheckOverlap(m_Block[y][x]->GetCollision().GetCollision()))
			{
				return m_Block[y][x];
			}
		}
	}

	return nullptr;
}
