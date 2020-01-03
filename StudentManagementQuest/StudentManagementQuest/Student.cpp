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
	cout << "이름을 입력 하시오 : ";
	cin >> m_Name;
	cout << "3과목의 점수를 입력하시오" << endl;
	cout << "국어 : ";
	cin >> m_Kor;
	cout << "영어 : ";
	cin >> m_Eng;
	cout << "수학 : ";
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
	cout << m_Num << "번 학생" << endl;
	cout << "이름 : " << m_Name << endl;
	cout << "국어 점수 : " << m_Kor << endl;
	cout << "수학 점수 : " << m_Eng << endl;
	cout << "영어 점수 : " << m_Math << endl;
	cout << "합계 점수 : " << m_Sum << "\t 평균 점수 : " << m_Avg << endl;
	cout << "등급 : [ " << m_Class << "]" << endl << endl;
	return;
}
