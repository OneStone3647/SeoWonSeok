#include <stdio.h>

int main()
{
	int num1;
	printf("높이 입력 : ");
	scanf_s("%d", &num1);

	for (int i = 1; i <= num1; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("★");
		}
		printf("\n");
	}

	return 0;
}