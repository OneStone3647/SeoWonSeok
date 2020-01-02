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
	// i: num의 자릿수, j: 새로운 자릿수, k: 각 자리의 숫자, temp: k의 추출을 위한 매개변수, newnum: 거꾸로 수
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

	printf("1.두 수를 입력 하시오 : ");
	scanf_s("%d%d", &num1, &num2);
	printf("%d와 %d중 큰 수는 %d 입니다.\n", num1, num2, Big(num1, num2));

	printf("2.정수 하나를 입력하시오 : ");
	scanf_s("%d", &num1);
	printf("%d는 ", num1);
	if (Which(num1))
	{
		printf("짝수 입니다.\n");
	}
	else
	{
		printf("홀수 입니다.\n");
	}

	printf("3.정수 하나를 입력하시오 : ");
	scanf_s("%d", &num1);
	printf("%d의 절대값 : %d\n", num1, Abs(num1));

	printf("4.정수 하나를 입력하시오 : ");
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

	printf("5.정수 하나를 입력하시오 : ");
	scanf_s("%d", &num1);
	printf("%d의 거꾸로 수 : %d\n", num1, Change(num1));

	return 0;
}