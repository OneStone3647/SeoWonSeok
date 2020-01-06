#include "Std_Manager.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 1003;

	// A¾È
	Std_Manager::GetInstance()->Display();
}