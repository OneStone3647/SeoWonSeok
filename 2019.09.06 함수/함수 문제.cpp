#include <stdio.h>

int Big(int num1, int num2)
{
	if (num1 > num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}

bool Which(int num)
{
	if (num % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Abs(int num)
{
	return num > 0 ? num : num * (-1);
}

bool Three(int num)
{
	if (num % 3 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Change(int num)
{
	// i: num�� �ڸ���, j: ���ο� �ڸ���, k: �� �ڸ��� ����, temp: k�� ������ ���� �Ű�����, newnum: �Ųٷ� ��
	int i = 1, j = 1, temp = 0, newnum = 0;

	while (i <= num)
	{
		i *= 10;
	}
	i /= 10;

	for (int k = 0; i != 0; i /= 10)
	{
		k = (num - temp) / i;
		temp += (i*k);

		while (1)
		{
			newnum = newnum + (k*j);
			break;
		}
		j *= 10;
	}

	return newnum;
}

int main()
{
	int num1, num2;

	printf("1.�� ���� �Է� �Ͻÿ� : ");
	scanf_s("%d%d", &num1, &num2);
	printf("%d�� %d�� ū ���� %d �Դϴ�.\n", num1, num2, Big(num1, num2));

	printf("2.���� �ϳ��� �Է��Ͻÿ� : ");
	scanf_s("%d", &num1);
	printf("%d�� ", num1);
	if (Which(num1))
	{
		printf("¦�� �Դϴ�.\n");
	}
	else
	{
		printf("Ȧ�� �Դϴ�.\n");
	}

	printf("3.���� �ϳ��� �Է��Ͻÿ� : ");
	scanf_s("%d", &num1);
	printf("%d�� ���밪 : %d\n", num1, Abs(num1));

	printf("4.���� �ϳ��� �Է��Ͻÿ� : ");
	scanf_s("%d", &num1);
	for (int i = 1; i <= num1; i++)
	{
		if (Three(i))
		{
			if (i == 3)
			{
				printf("%d", i);
			}
			else
			{
				printf(",%d", i);
			}
		}
	}
	printf("\n");

	printf("5.���� �ϳ��� �Է��Ͻÿ� : ");
	scanf_s("%d", &num1);
	printf("%d�� �Ųٷ� �� : %d\n", num1, Change(num1));

	return 0;
}