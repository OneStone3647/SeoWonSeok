#include "Student.h"



Student::Student()
{
	m_Num = 0;
}


Student::~Student()
{
}

void Student::SetStudent(int num)
{
	cout << "�̸��� �Է� �Ͻÿ� : ";
	cin >> m_Name;
	cout << "3������ ������ �Է��Ͻÿ�" << endl;
	cout << "���� : ";
	cin >> m_Kor;
	cout << "���� : ";
	cin >> m_Eng;
	cout << "���� : ";
	cin >> m_Math;
	m_Sum = m_Kor + m_Eng + m_Math;
	m_Avg = (float)m_Sum / 3;
	m_Num = num;
	if (m_Avg > 90)
	{
		m_Class = 'A';
	}
	else if (m_Avg >= 80)
	{
		m_Class = 'B';
	}
	else if (m_Avg >= 70)
	{
		m_Class = 'C';
	}
	else if (m_Avg >= 60)
	{
		m_Class = 'D';
	}
	else
	{
		m_Class = 'F';
	}
	return;
}

void Student::ShowStudent()
{
	cout << "----------------------" << endl;
	cout << m_Num << "�� �л�" << endl;
	cout << "�̸� : " << m_Name << endl;
	cout << "���� ���� : " << m_Kor << endl;
	cout << "���� ���� : " << m_Eng << endl;
	cout << "���� ���� : " << m_Math << endl;
	cout << "�հ� ���� : " << m_Sum << "\t ��� ���� : " << m_Avg << endl;
	cout << "��� : [ " << m_Class << "]" << endl << endl;
	return;
}
