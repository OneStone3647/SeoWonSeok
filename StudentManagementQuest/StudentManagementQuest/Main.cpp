#include "Std_Manager.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 1003;

	Std_Manager::GetInstance()->Display();
	Std_Manager::GetInstance()->DestroyInstance();
}