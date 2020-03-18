#include "BlockManager.h"



BlockManager::BlockManager()
{
}


BlockManager::~BlockManager()
{
}

void BlockManager::Init(HDC MemDC, int MapSizeX, int MapSizeY, int BlockStartX, int BlockStartY)
{
	m_MemDC = MemDC;

	m_MapX = MapSizeX;
	m_MapY = MapSizeY;
	m_BlockStartX = BlockStartX;
	m_BlockStartY = BlockStartY;

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
	m_Block.reserve(m_MapY);
	for (int y = 0; y < m_MapY; y++)
	{
		vector<Block*> tmpBlock;
		// ������ ���� ���� �޸� ũ�� ����
		tmpBlock.reserve(m_MapX);
		for (int x = 0; x < m_MapX; x++)
		{
			Safe* tmpSafe = new Safe;
			tmpSafe->Init(m_MemDC, x, y, m_BlockStartX, m_BlockStartY);
			tmpBlock.push_back(tmpSafe);
		}
		m_Block.push_back(tmpBlock);
	}
}

void BlockManager::Release()
{
	// Block Ŭ���� ������ ���� ���� �Ҵ� ����
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
}

void BlockManager::DrawAllBlock()
{
	vector<vector<Block*>>::iterator iterY;
	vector<Block*>::iterator iterX;
	for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
	{
		for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
		{
			(*iterX)->Draw();
		}
	}
}

void BlockManager::CheckBlock(MOUSECLICK PlayerClick, POINT MousePoint)
{
	for (int y = 0; y < m_MapY; y++)
	{
		for (int x = 0; x < m_MapX; x++)
		{
			if (PlayerClick == MOUSECLICK_LEFT && PtInRect(&m_Block[y][x]->GetCollision(), MousePoint))
			{
				m_Block[y][x]->SetIsFlag(false);
				m_Block[y][x]->IsOpen();
			}
			else if(PlayerClick == MOUSECLICK_RIGHT && PtInRect(&m_Block[y][x]->GetCollision(), MousePoint))
			{
				if (m_Block[y][x]->GetIsFlag())
				{
					m_Block[y][x]->SetIsFlag(false);
				}
				else
				{
					m_Block[y][x]->SetIsFlag(true);
				}
			}
		}
	}
}
