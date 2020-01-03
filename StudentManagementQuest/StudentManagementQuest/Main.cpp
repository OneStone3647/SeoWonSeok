#include "Std_Manager.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 1003;

	// A��
	//Std_Manager::GetInstance()->Display();
	//Std_Manager::GetInstance()->DestroyInstance();

	// B�� Display()�� ���� �θ��� �ʰ� Main���� ����
	int select;
	while (true)
	{
		system("cls");
		cout << "=========================" << endl;
		cout << "   1.�л� ���" << endl;
		cout << "   2.��ü �л����� ���" << endl;
		cout << "   3.�л� ��ȣ �˻�" << endl;
		cout << "   4.�л� �̸� �˻�" << endl;
		cout << "   5.��޺� ���" << endl;
		cout << "   0.����" << endl;
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
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		}
		system("pause");
	}
}