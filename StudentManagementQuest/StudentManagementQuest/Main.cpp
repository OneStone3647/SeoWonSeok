#include "Std_Manager.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 1003;

	// A안
	//Std_Manager::GetInstance()->Display();
	//Std_Manager::GetInstance()->DestroyInstance();

	// B안 Display()할 수를 부르지 않고 Main에서 실행
	int select;
	while (true)
	{
		system("cls");
		cout << "=========================" << endl;
		cout << "   1.학생 등록" << endl;
		cout << "   2.전체 학생정보 출력" << endl;
		cout << "   3.학생 번호 검색" << endl;
		cout << "   4.학생 이름 검색" << endl;
		cout << "   5.등급별 출력" << endl;
		cout << "   0.종료" << endl;
		cout << "=========================" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			Std_Manager::GetInstance()->SetStudent();
			break;
		case 2:
			Std_Manager::GetInstance()->ShowStudent();
			break;
		case 3:
			Std_Manager::GetInstance()->FindNumber();
			break;
		case 4:
			Std_Manager::GetInstance()->FindName();
			break;
		case 5:
			Std_Manager::GetInstance()->FindClass();
			break;
		case 0:
			Std_Manager::GetInstance()->DestroyInstance();
			return;
		default:
			cout << "잘못 입력하셨습니다." << endl;
		}
		system("pause");
	}
}