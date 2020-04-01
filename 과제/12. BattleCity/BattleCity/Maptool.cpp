#include "Maptool.h"

Maptool* Maptool::m_pThis = NULL;

Maptool::Maptool()
{
}


Maptool::~Maptool()
{
	Release();
}

void Maptool::Init(HWND hWnd)
{
	m_ScreenSize.cx = MaptoolWidth;
	m_ScreenSize.cy = MaptoolHeight;

	m_hWnd = hWnd;
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� ScreenWidth, ���� ScreenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, m_ScreenSize.cx, m_ScreenSize.cy);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	MoveWindow(m_hWnd, WindowPosX, WindowPosY, m_ScreenSize.cx, m_ScreenSize.cy, TRUE);

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
			newBlock->Init(m_MemDC, x * BlockSizeX, y * BlockSizeY);
			tmpBlock.push_back(newBlock);
		}
		m_Block.push_back(tmpBlock);
	}

	m_BlockBitmapCount = 15;
	// Bitmap Ŭ���� ���Ͱ� �̹� ������ ��� �Ҵ� �����Ѵ�.
	if (!m_BlockBitmap.empty())
	{
		vector<Block*>::iterator iter;
		for (iter = m_BlockBitmap.begin(); iter != m_BlockBitmap.end(); iter++)
		{
			delete (*iter);
		}
		m_BlockBitmap.clear();
		vector<Block*>().swap(m_BlockBitmap);
	}
	// Bitmap Ŭ���� ���� �����Ҵ�
	// ���� �޸� ũ�� ����
	m_BlockBitmap.reserve(m_BlockBitmapCount);
	for (int i = 0; i < m_BlockBitmapCount; i++)
	{
		Block* tmpBitmap = new Block;
		tmpBitmap->Init(m_MemDC, 1400, i * (BlockSizeY + 5) + 10);
		if (i == m_BlockBitmapCount - 1)
		{
			tmpBitmap->SetBlockType(BLOCKTYPE_EMPTY);
		}
		else
		{
			tmpBitmap->SetBlockType((BLOCKTYPE)i);
		}
		m_BlockBitmap.push_back(tmpBitmap);
	}

	m_CurSelectBlock = BLOCKTYPE_EMPTY;

	m_SaveButton = { 100, 760, 300, 810 };
	m_LoadButton = { 400, 760, 600, 810 };

	m_CurMode = FILEMODE_IDLE;

	m_NullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	m_WhiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_SelectPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	m_LinePen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}

void Maptool::Release()
{
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);

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

	// Bitmap Ŭ���� ���� ���� �Ҵ� ����
	if (!m_BlockBitmap.empty())
	{
		vector<Block*>::iterator iter;
		for (iter = m_BlockBitmap.begin(); iter != m_BlockBitmap.end(); iter++)
		{
			delete (*iter);
		}
		m_BlockBitmap.clear();
		vector<Block*>().swap(m_BlockBitmap);
	}

	DeleteObject(m_NullBrush);
	DeleteObject(m_WhiteBrush);
	DeleteObject(m_SelectPen);
	DeleteObject(m_LinePen);
}

void Maptool::Update(LPARAM lParam)
{
	DrawBackGround();
	DrawSelectBlock(lParam);
	DrawButton(lParam);

	if (Input(lParam) && PtInRect(&m_SaveButton, m_MousePoint))
	{
		m_CurMode = FILEMODE_SAVE;
	}
	else if (Input(lParam) && PtInRect(&m_LoadButton, m_MousePoint))
	{
		m_CurMode = FILEMODE_LOAD;
	}

	if (m_CurMode != FILEMODE_IDLE)
	{
		SaveLoad();
	}
	
	// m_MemDC�� m_NullBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_NullBrush);
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, m_LinePen);

	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (Input(lParam) && m_Block[y][x]->GetCollision().CheckMouseHit(m_MousePoint))
			{
				m_Block[y][x]->SetBlockType(m_CurSelectBlock);
			}

			if (m_Block[y][x]->GetBlockType() != BLOCKTYPE_EMPTY)
			{
				m_Block[y][x]->Draw();
			}
			else
			{
				Rectangle(m_MemDC, m_Block[y][x]->GetBlockPoint().x, m_Block[y][x]->GetBlockPoint().y, m_Block[y][x]->GetBlockPoint().x + BlockSizeX, m_Block[y][x]->GetBlockPoint().y + BlockSizeY);
			}
		}
	}

	// m_MemDC�� oldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, oldBrush);
	// m_MemDC�� oldPen�� �����Ѵ�.
	SelectObject(m_MemDC, oldPen);
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, MaptoolWidth, MaptoolHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void Maptool::DrawBackGround()
{
	// m_MemDC�� m_WhiteBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_WhiteBrush);

	Rectangle(m_MemDC, 0, 0, MaptoolWidth, MaptoolHeight);
	Rectangle(m_MemDC, 0, 0, GameWidth, GameHeight);

	// m_MemDC�� m_OldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, oldBrush);
}

void Maptool::DrawSelectBlock(LPARAM lParam)
{
	// m_MemDC�� m_NullBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush;
	HPEN oldPen;

	for (vector<Bitmap*>::size_type i = 0; i < m_BlockBitmap.size(); ++i)
	{
		if (Input(lParam) && m_BlockBitmap[i]->GetCollision().CheckMouseHit(m_MousePoint))
		{
			m_CurSelectBlock = (BLOCKTYPE)i;
		}

		if (m_CurSelectBlock == m_BlockBitmap[i]->GetBlockType())
		{
			oldPen = (HPEN)SelectObject(m_MemDC, m_SelectPen);
		}
		else
		{
			oldPen = (HPEN)SelectObject(m_MemDC, m_LinePen);
		}
		oldBrush = (HBRUSH)SelectObject(m_MemDC, m_NullBrush);
		if (i != m_BlockBitmap.size() - 1)
		{
			m_BlockBitmap[i]->Draw();
		}

		Rectangle(m_MemDC, m_BlockBitmap[i]->GetBlockPoint().x, m_BlockBitmap[i]->GetBlockPoint().y, m_BlockBitmap[i]->GetBlockPoint().x + BlockSizeX, m_BlockBitmap[i]->GetBlockPoint().y + BlockSizeY);

		// m_MemDC�� oldBrush�� �����Ѵ�.
		SelectObject(m_MemDC, oldBrush);
		// m_MemDC�� oldPen�� �����Ѵ�.
		SelectObject(m_MemDC, oldPen);
	}
}

bool Maptool::Input(LPARAM lParam)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_MousePoint.x = LOWORD(lParam);
		m_MousePoint.y = HIWORD(lParam);
		return true;
	}

	return false;
}

void Maptool::DrawButton(LPARAM lParam)
{
	// m_MemDC�� m_NullBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_NullBrush);
	HPEN oldPen = (HPEN)SelectObject(m_MemDC, m_LinePen);

	Rectangle(m_MemDC, m_SaveButton.left, m_SaveButton.top, m_SaveButton.right, m_SaveButton.bottom);
	char save[256] = "Save";
	TextOut(m_MemDC, m_SaveButton.left + 80, m_SaveButton.top + 15, save, strlen(save));
	Rectangle(m_MemDC, m_LoadButton.left, m_LoadButton.top, m_LoadButton.right, m_LoadButton.bottom);
	char load[256] = "Load";
	TextOut(m_MemDC, m_LoadButton.left + 80, m_LoadButton.top + 15, load, strlen(load));

	SelectObject(m_MemDC, oldBrush);
	SelectObject(m_MemDC, oldPen);
}

void Maptool::SaveLoad()
{
	OPENFILENAME OFN;
	char str[300];
	char lpstrFile[MAX_PATH] = "";
	char lpstrPath[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	GetCurrentDirectory(MAX_PATH, lpstrPath);
	OFN.lpstrInitialDir = lpstrPath;
	if (GetSaveFileName(&OFN) == 0)
	{
		DWORD err = CommDlgExtendedError();
		return;
	}

	switch (m_CurMode)
	{
	case FILEMODE_IDLE:
		return;

	case FILEMODE_SAVE: 
		{
			HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
			{
				for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
				{
					DWORD writeB;
					int tmpInt = m_Block[y][x]->GetBlockType();
					WriteFile(hFile, &tmpInt, sizeof(int), &writeB, NULL);
				}
			}
			CloseHandle(hFile);
			m_CurMode = FILEMODE_IDLE;
		}
		break;

	case FILEMODE_LOAD:
		{
			HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
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
			m_CurMode = FILEMODE_IDLE;
		}
		break;
	}
}
