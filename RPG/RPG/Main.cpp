#include "GameManager.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 1003;

	GameManager* GManager = new Game();

	GManager->Initialized();
	GManager->Update();
	GManager->Finishied();

	delete GManager;
}