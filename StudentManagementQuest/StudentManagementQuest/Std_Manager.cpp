#include "Std_Manager.h"

Std_Manager* Std_Manager::m_pThis = NULL;

Std_Manager::Std_Manager()
{
	// ���� �Ҵ�
	for (int i = 0; i < 30; i++)
	{
		m_Std[i] = new Student;
	}
}

void Std_Manager::Display()
{
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
			GetInstance()->SetStudent();
			break;
		case 2:
			GetInstance()->ShowStudent();
			break;
		case 3:
			GetInstance()->FindNumber();
			break;
		case 4:
			GetInstance()->FindName();
			break;
		case 5:
			GetInstance()->FindClass();
			break;
		case 0:
			DestroyInstance();
			return;
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		}
		system("pause");
	}
}

void Std_Manager::SetStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetNum() == 0)
		{
			m_Std[i]->SetStudent(i + 1);
			return;
		}
	}
	cout << "�л��� ���� ��� �Ǿ����ϴ�." << endl;
}

void Std_Manager::ShowStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetNum() != 0)
		{
			m_Std[i]->ShowStudent();
		}
		else
		{
			return;
		}
	}
}

void Std_Manager::FindNumber()
{
	int findNum;
	cout << "ã�� �л��� ��ȣ�� �Է� �Ͻÿ�.";
	cin >> findNum;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetNum() == findNum)
		{
			m_Std[i]->ShowStudent();
			return;
		}
	}
	cout << endl << "�ش� ��ȣ�� �л��� �����ϴ�." << endl;
}

void Std_Manager::FindName()
{
	string findStr;
	int findNum = 0;
	cout << "ã�� �л��� �̸��� �Է� �Ͻÿ�.";
	cin >> findStr;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetName() == findStr)
		{
			m_Std[i]->ShowStudent();
			findNum++;
		}
	}
	if (findNum == 0)
	{
		cout << "�ش� �̸��� �л��� �����ϴ�." << endl;
	}
}

void Std_Manager::FindClass()
{
	int findNum = 0;
	cout << "========= [ A ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetClass() == 'A')
		{
			m_Std[i]->ShowStudent();
			findNum++;
		}
	}
	cout << "�� " << findNum << "��" << endl;	
	cout << "=========================" << endl << endl << endl;
	findNum = 0;
	cout << "========= [ B ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetClass() == 'B')
		{
			m_Std[i]->ShowStudent();
			findNum++;
		}
	}
	cout << "�� " << findNum << "��" << endl;
	cout << "=========================" << endl << endl << endl;
	findNum = 0;
	cout << "========= [ C ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetClass() == 'C')
		{
			m_Std[i]->ShowStudent();
			findNum++;
		}
	}
	cout << "�� " << findNum << "��" << endl;
	cout << "=========================" << endl << endl << endl;
	findNum = 0;
	cout << "========= [ D ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetClass() == 'D')
		{
			m_Std[i]->ShowStudent();
			findNum++;
		}
	}
	cout << "�� " << findNum << "��" << endl;
	cout << "=========================" << endl << endl << endl;
	findNum = 0;
	cout << "========= [ F ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetClass() == 'F')
		{
			m_Std[i]->ShowStudent();
			findNum++;
		}
	}
	cout << "�� " << findNum << "��" << endl;
	cout << "=========================" << endl << endl << endl;
}


Std_Manager::~Std_Manager()
{
	for (int i = 0; i < 30; i++)
	{
		delete m_Std[i];
	}
}
