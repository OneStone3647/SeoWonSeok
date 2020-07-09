#include "Paper.h"
#include "ResoucesManager.h"
#include "defines.h"



Paper::Paper()
{
}


Paper::~Paper()
{
}

void Paper::Init(int color)
{
	m_Color = color;
	switch (m_Color)
	{
	case COLOR_GREEN:
		m_Paper = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperGreen.bmp");
		break;
	case COLOR_YELLOW:
		m_Paper = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperYellow.bmp");
		break;
	case COLOR_RED:
		m_Paper = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperRed.bmp");
		break;
	case COLOR_BLUE:
		m_Paper = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperBlue.bmp");
		break;
	}
}
