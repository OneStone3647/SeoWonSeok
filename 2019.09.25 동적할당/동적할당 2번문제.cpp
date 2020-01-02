#include <iostream>
#include <string>
#include <Windows.h>

#define MAX 10

using namespace std;

struct Student
{
	string name;
	int studentCount;
	int age;
	int grade;
	int num;
	int language;
	int english;
	int math;
	int totalScore;
	int averScore;
	char rankScore;
};

int studentCount = 0;

int TotalScore(int language, int english, int math)
{
	return language + english + math;
}

int AverageScore(int totalScore)
{
	return totalScore / 3;
}

char RankScore(int averageScore)
{
	if (averageScore >= 90)
	{
		return 'A';
	}
	else if (averageScore >= 80)
	{
		return 'B';
	}
	else if (averageScore >= 70)
	{
		return 'C';
	}
	else if (averageScore >= 60)
	{
		return 'D';
	}
	else if (averageScore < 60)
	{
		return 'F';
	}
}

void SetStudent(Student* student, int* studentCount)
{
	cout << '\t' << "======" << (*studentCount) << "��° �л�======" << endl;
	student->studentCount = (*studentCount);
	cout << '\t' << "�̸� : ";
	cin >> student->name;
	cout << '\t' << "����: ";
	cin >> student->age;
	while (1)
	{
		cout << '\t' << "�г�(1~3) : ";
		cin >> student->grade;
		if (student->grade >= 1 && student->grade <= 3)
		{
			break;
		}
		cout << "�߸� �Է� �ٽ�" << endl;
	}
	cout << '\t' << "�������� : ";
	cin >> student->language;
	cout << '\t' << "�������� : ";
	cin >> student->english;
	cout << '\t' << "�������� : ";
	cin >> student->math;

	// �հ� ����
	student->totalScore = TotalScore(student->language, student->english, student->math);
	// ��� ����
	student->averScore = AverageScore(student->totalScore);
	// ����
	student->rankScore = RankScore(student->averScore);
	
	*studentCount += 1;
}

void ShowStudent(Student* student)
{
	cout << "  " << "======" << student->studentCount << "��° �л�======" << endl;
	cout << "  " << "�̸� : " << student->name << endl;
	cout << "  " << "����: " << student->age << endl;
	cout << "  " << "�г�(1~3) : " << student->grade << endl;
	cout << "  " << "�������� : " << student->language << endl;
	cout << "  " << "�������� : " << student->english << endl;
	cout << "  " << "�������� : " << student->math << endl;
	cout << "  " << "�հ� ���� : " << student->totalScore << "  " << "��� ���� : " << student->averScore << endl;
	cout << "  " << "��� : [" << student->rankScore << "]" << endl << endl;
}

void SearchStudent(Student** student)
{
	string searchName;
	system("cls");
	cout << "�̸� �Է� : ";
	cin >> searchName;

	if (searchName != (*student)->name)
	{
		cout << "�ش� �л��� �����ϴ�." << endl;
	}
	else
	{
		ShowStudent((*student));
	}
	system("pause");
}

void ShowRank(Student* student[], int studentCount, char rank)
{
	cout << "��������������������" << rank << " ��ަ�������������������" << endl;
	for (int i = 0; i < studentCount; i++)
	{
		if (student[i]->rankScore == rank)
			ShowStudent(student[i]);
	}
	printf("����������������������������������������������\n");
}

void ShowGrade(Student* student[], int studentCount, int grade)
{
	cout << "��������������������" << grade << " �г⦡������������������" << endl;
	for (int i = 0; i < studentCount; i++)
	{
		if (student[i]->grade == grade)
			ShowStudent(student[i]);
	}
	printf("����������������������������������������������\n");
}

int main()
{
	int select;
	Student* student_List[MAX];

	while (1)
	{
		system("cls");
		cout << "===�л���������===(�л��� : " << studentCount << "��)" << endl;
		cout << "1,�л����" << endl;
		cout << "2.�л����� ����" << endl;
		cout << "3.�л� �˻�" << endl;
		cout << "4.��޺� ����" << endl;
		cout << "5.�г⺰ ����" << endl;
		cout << "6.����" << endl;
		cout << "�Է� : ";
		cin >> select;

		switch (select)
		{
		case 1:
			system("cls");
			student_List[studentCount] = new Student;
			SetStudent(student_List[studentCount], &studentCount);
			break;
		case 2:
			system("cls");
			for (int i = 0; i < studentCount; i++)
			{
				ShowStudent(student_List[i]);
			}
			system("pause");
			break;
		case 3:
			SearchStudent(student_List);
			break;
		case 4:
			system("cls");
			for (int i = 'A'; i <= 'F'; i++)
			{
				if (i != 'E')
				{
					ShowRank(student_List, studentCount, i);
				}
			}
			system("pause");
			break;
		case 5:
			system("cls");
			for (int i = 1; i <= 3; i++)
			{
				ShowGrade(student_List, studentCount, i);
			}
			system("pause");
			break;
		case 6:
			for (int i = 0; i < studentCount; i++)
			{
				cout << student_List[i]->num << "�� �л�" << student_List[i]->name << endl;
				delete student_List[i];
				cout << "�Ҵ� ���� �Ϸ�" << endl;
			}
			system("pause");
			return 0;
		}
	}
}