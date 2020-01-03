#pragma once
#include "Student.h"
#include "Singleton.h"
#include <Windows.h>

// ΩÃ±€≈Ê ªÛº”
class Std_Manager : public Singleton<Std_Manager>
{
private:
	Student* m_Std[30];
public:
	Std_Manager();
	void Display();
	void SetStudent();
	void ShowStudent();
	void FindNumber();
	void FindName();
	void FindClass();
	~Std_Manager();
};

