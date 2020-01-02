#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#define MAX 50

typedef struct student
{
	char Name[10];
	int Age;
	int Class;
	int Number;
	char Gender[10];
}Student;

void ShowStudent(Student* St)
{
	printf("======%s�л�(%d��)======\n", St->Name, St->Number);
	printf("���� : %d, ���� : %s, �г� : %d\n", St->Age, St->Gender, St->Class);
	printf("======================\n");
}

void ShowClassStudent(Student* St[], int StCount, int StClass)
{
	printf("����������������%d �г⦡������������\n", StClass);
	for (int i = 0; i < StCount; i++)
	{
		if (St[i]->Class == StClass)
		{
			ShowStudent(St[i]);
		}
	}
	printf("������������������������������������\n");
}

void SetStudent(Student* St, int *StudentCount)
{
	St->Number = ++(*StudentCount);
	printf("======%d�� �л�======\n", St->Number);
	printf("�̸� �Է� : ");
	scanf("%s", St->Name);
	printf("���� �Է� : ");
	scanf("%d", &St->Age);
	printf("���� �Է� : ");
	scanf("%s", St->Gender);
	printf("�г� �Է�(1~3) : ");
	scanf("%d", &St->Class);
	while (St->Class == 0 || St->Class > 3)
	{
		printf("�г� �߸� �Է�(���� 1~3�г�)\n");
		system("pause");
		printf("�г� �Է�(1~3) : ");
		scanf("%d", &St->Class);
	}
}

int main()
{
	Student* Student_List[MAX];
	int Select;
	int StudentCount = 0;
	char NameTemp[10];

	while (1)
	{
		system("cls");
		printf("=====�л��������α׷�=====(�� �ο� : %d)\n", StudentCount);
		printf("1.�л� ���\n");
		printf("2.�л� ���(��ȣ��)\n");
		printf("3.�л� ���(�г��)\n");	//
		printf("4.�г� �˻�\n");		//
		printf("5.�л� �˻�\n");
		printf("6.������ �л� ����\n");
		printf("7.�л� ��ü ����\n");
		printf("8.����\n");
		printf("�Է� : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			system("cls");
			if (StudentCount + 1 >= 50)
			{
				printf("�л�����(50��)�� ��� á���ϴ�.\n");
				system("pause");
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student));
			SetStudent(Student_List[StudentCount], &StudentCount);
			break;
		case 2:
			system("cls");
			for (int i = 0; i < StudentCount; i++)
			{
				ShowStudent(Student_List[i]);
			}
			system("pause");
			break;
		case 3:
			system("cls");	
			for (int i = 1; i <= 3; i++)
			{
				ShowClassStudent(Student_List, StudentCount, i);
			}
			system("pause");
			break;
		case 4:
			int Select;
			system("cls");
			printf("�˻��� �г� �Է�(1~3) : ");
			scanf("%d", &Select);
			while (Select < 1 || Select > 3)
			{
				printf("�г� �߸� �Է�(���� 1~3�г�)\n");
				system("pause");
				printf("�г� �Է�(1~3) : ");
				scanf("%d", &Select);
			}
			ShowClassStudent(Student_List, StudentCount, Select);
			system("pause");
			break;
		case 5:
			system("cls");
			printf("�˻��� �̸� �Է� : ");
			scanf("%s", NameTemp);
			for (int i = 0; i < StudentCount; i++)
			{
				if (strcmp(NameTemp, Student_List[i]->Name))
				{
					ShowStudent(Student_List[i]);
				}
			}
			system("pause");
			break;
		case 6:
			if (StudentCount - 1 < 0)
			{
				printf("�� �̻� ������ �л��� �����ϴ�. \n");
				system("pause");
				break;
			}
			StudentCount--;
			ShowStudent(Student_List[StudentCount]);
			free(Student_List[StudentCount]);
			Student_List[StudentCount] = NULL;
			printf("���� �Ϸ�");
			system("pause");
			break;
		case 7:
			for (int i = 0; i < StudentCount; i++)
			{
				ShowStudent(Student_List[i]);
				free(Student_List[i]);
				Student_List[i] = NULL;
				printf("���� �Ϸ�");
			}
			StudentCount = 0;
			system("pause");
			break;
		case 8:
			for (int i = 0; i < StudentCount; i++)
			{
				printf("%s�л� �����Ҵ� ���� �Ϸ�\n", Student_List[i]->Name);
				free(Student_List[i]);
			}
			system("pause");
			return 0;
		}
	}

	return 0;
}