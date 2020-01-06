#include "Std_Manager.h"

Std_Manager* Std_Manager::m_pThis = NULL;

Std_Manager::Std_Manager()
{
	// 동적 할당
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
			cout << "잘못 입력하셨습니다." << endl;
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
	cout << "학생이 전원 등록 되었습니다." << endl;
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
	cout << "찾을 학생의 번호를 입력 하시오.";
	cin >> findNum;
	for (int i = 0; i < 30; i++)
	{
		if (m_Std[i]->GetNum() == findNum)
		{
			m_Std[i]->ShowStudent();
			return;
		}
	}
	cout << endl << "해당 번호의 학생이 없습니다." << endl;
}

void Std_Manager::FindName()
{
	string findStr;
	int findNum = 0;
	cout << "찾을 학생의 이름을 입력 하시오.";
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
		cout << "해당 이름의 학생이 없습니다." << endl;
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
	cout << "총 " << findNum << "명" << endl;	
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
	cout << "총 " << findNum << "명" << endl;
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
	cout << "총 " << findNum << "명" << endl;
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
	cout << "총 " << findNum << "명" << endl;
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
	cout << "총 " << findNum << "명" << endl;
	cout << "=========================" << endl << endl << endl;
}


Std_Manager::~Std_Manager()
{
	for (int i = 0; i < 30; i++)
	{
		delete m_Std[i];
	}
}
