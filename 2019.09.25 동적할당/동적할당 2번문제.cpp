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
	cout << '\t' << "======" << (*studentCount) << "번째 학생======" << endl;
	student->studentCount = (*studentCount);
	cout << '\t' << "이름 : ";
	cin >> student->name;
	cout << '\t' << "나이: ";
	cin >> student->age;
	while (1)
	{
		cout << '\t' << "학년(1~3) : ";
		cin >> student->grade;
		if (student->grade >= 1 && student->grade <= 3)
		{
			break;
		}
		cout << "잘못 입력 다시" << endl;
	}
	cout << '\t' << "국어점수 : ";
	cin >> student->language;
	cout << '\t' << "영어점수 : ";
	cin >> student->english;
	cout << '\t' << "수학점수 : ";
	cin >> student->math;

	// 합계 점수
	student->totalScore = TotalScore(student->language, student->english, student->math);
	// 평균 점수
	student->averScore = AverageScore(student->totalScore);
	// 학점
	student->rankScore = RankScore(student->averScore);
	
	*studentCount += 1;
}

void ShowStudent(Student* student)
{
	cout << "  " << "======" << student->studentCount << "번째 학생======" << endl;
	cout << "  " << "이름 : " << student->name << endl;
	cout << "  " << "나이: " << student->age << endl;
	cout << "  " << "학년(1~3) : " << student->grade << endl;
	cout << "  " << "국어점수 : " << student->language << endl;
	cout << "  " << "영어점수 : " << student->english << endl;
	cout << "  " << "수학점수 : " << student->math << endl;
	cout << "  " << "합계 점수 : " << student->totalScore << "  " << "평균 점수 : " << student->averScore << endl;
	cout << "  " << "등급 : [" << student->rankScore << "]" << endl << endl;
}

void SearchStudent(Student** student)
{
	string searchName;
	system("cls");
	cout << "이름 입력 : ";
	cin >> searchName;

	if (searchName != (*student)->name)
	{
		cout << "해당 학생이 없습니다." << endl;
	}
	else
	{
		ShowStudent((*student));
	}
	system("pause");
}

void ShowRank(Student* student[], int studentCount, char rank)
{
	cout << "┌─────────" << rank << " 등급─────────┐" << endl;
	for (int i = 0; i < studentCount; i++)
	{
		if (student[i]->rankScore == rank)
			ShowStudent(student[i]);
	}
	printf("└─────────────────────┘\n");
}

void ShowGrade(Student* student[], int studentCount, int grade)
{
	cout << "┌─────────" << grade << " 학년─────────┐" << endl;
	for (int i = 0; i < studentCount; i++)
	{
		if (student[i]->grade == grade)
			ShowStudent(student[i]);
	}
	printf("└─────────────────────┘\n");
}

int main()
{
	int select;
	Student* student_List[MAX];

	while (1)
	{
		system("cls");
		cout << "===학생정보관리===(학생수 : " << studentCount << "명)" << endl;
		cout << "1,학생등록" << endl;
		cout << "2.학생정보 보기" << endl;
		cout << "3.학생 검색" << endl;
		cout << "4.등급별 보기" << endl;
		cout << "5.학년별 보기" << endl;
		cout << "6.종료" << endl;
		cout << "입력 : ";
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
				cout << student_List[i]->num << "번 학생" << student_List[i]->name << endl;
				delete student_List[i];
				cout << "할당 해제 완료" << endl;
			}
			system("pause");
			return 0;
		}
	}
}