#include "King.h"



King::King()
{
}

void King::Move(HDC hdc, int x, int y)
{
	TransparentBlt(hdc, BLOCKX * x, BLOCKX * y, BLOCKX, BLOCKY, MemDC, 0, 0, BLOCKX, BLOCKY, RGB(255, 0, 255));
}


King::~King()
{
}
