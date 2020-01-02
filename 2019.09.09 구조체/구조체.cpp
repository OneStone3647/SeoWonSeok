#include<stdio.h>
#include <Windows.h>

typedef struct people
{
	char Name[10];
	int Age;
	float Height;
}People;

void SetPeople(People* P)
{
	for (int i = 0; i < 5; i++)
	{
		printf("======%d======\n", i + 1);
		printf("�̸��Է� : ");
		scanf_s("%s", P[i].Name, sizeof(P[i].Name));
		printf("�����Է� : ");
		scanf_s("%d", &P[i].Age);
		printf("Ű�Է� : ");
		scanf_s("%f", &P[i].Height);
		printf("==============\n");
	}
}

void ShowPeople(People* P)
{
	for (int i = 0; i < 5; i++)
	{
		printf("======%d======\n", i + 1);
		printf("�̸� : %s\n", P[i].Name);
		printf("���� : %d\n", P[i].Age);
		printf("Ű : %.2f\n", P[i].Height);
		printf("==============\n");
	}
}

void InsertionSort(People* P)
{
	People temp;
	int i, j;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4 - i; j++)
		{
			if (P[j].Age < P[j + 1].Age || (P[j].Age == P[j + 1].Age && P[j].Height < P[j + 1].Height))
			{
				temp = P[j];
				P[j] = P[j + 1];
				P[j + 1] = temp;
			}			
		}
	}
}

int main()
{
	People P_List[5];

	SetPeople(P_List);
	system("cls");
	printf("���� �� ����\n");
	ShowPeople(P_List);
	system("pause");

	InsertionSort(P_List);
	system("cls");
	ShowPeople(P_List);

	return 0;
}
