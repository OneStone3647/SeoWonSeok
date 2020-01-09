#include "CharacterFactory.h"
#include "GameManager.h"
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 207;

	//// Ãß»ó ÆÑÅä¸®
	//CharacterFactory* m_KnightFactory = new KnightFactory;
	//Character* m_Knight = m_KnightFactory->SpawnCharacter();
	//m_Knight->GetCharacterInfo();
	//cout << endl;

	//// Ãß»ó ÆÑÅä¸®
	//CharacterFactory* m_ArcherFactory = new ArcherFactory;
	//Character* m_Archer = m_ArcherFactory->SpawnCharacter();
	//m_Archer->GetCharacterInfo();
	//cout << endl;

	//// Ãß»ó ÆÑÅä¸®
	//CharacterFactory* m_WizardFactory = new WizardFactory;
	//Character* m_Wizard = m_WizardFactory->SpawnCharacter();
	//m_Wizard->GetCharacterInfo();
	//cout << endl;

	//system("pause");

	//delete m_Knight;
	//delete m_Archer;
	//delete m_Wizard;
	//delete m_KnightFactory;
	//delete m_ArcherFactory;
	//delete m_WizardFactory;

	GameManager GManager;
	GManager.Init();
	GManager.Update();
	GManager.Finish();
}