#include <stdio.h>

int main()
{
	int num1, num2;

	printf("가로와 세로를 입력하시오 : ");
	scanf_s("%d%d", &num1, &num2);

	for (int i = 0; i < num2; i++)
	{
		for (int j = 0; j < num1; j++)
		{
			if ((i == 0 || i == num2 - 1) || (j == 0 || j == num1 - 1))
			{
				printf("★");
			}
			else
			{
				printf("　");
			}
		}

		printf("\n");
	}

	return 0;
}