#pragma once
#include <iostream>
#include <string>
#include <crtdbg.h>

#define max_len 100

using namespace std;

class Student
{
private:
	string m_Name;
	int m_Kor, m_Eng, m_Math, m_Sum;
	float m_Avg;
	int m_Num;
	char m_Class;
public:
	Student();
	~Student();

	void SetStudent(int num);
	void ShowStudent();
	inline int GetNum()
	{
		return m_Num;
	}
	inline string GetName()
	{
		return m_Name;
	}
	inline char GetClass()
	{
		return m_Class;
	}
};

