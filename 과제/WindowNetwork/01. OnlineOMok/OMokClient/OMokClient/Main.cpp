#include "Mecro.h"
#include "NetManager.h"
#include "GameManager.h"

GameManager g_GameManager;

int main()
{
	NetManager::GetInstance()->Init();
	while (true)
	{
		if (NetManager::GetInstance()->GetsetTeam())
		{
			g_GameManager.Init();
			break;
		}
	}
	g_GameManager.Update();
	NetManager::GetInstance()->DestroyInstance();
	return 0;
}