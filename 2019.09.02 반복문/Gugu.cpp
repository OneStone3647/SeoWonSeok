#include <stdio.h>

int main()
{
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 2; j <= 9; j++)
		{
			if(i == 0)
			{
				printf("===%2d´Ü===   ", j);
			}
			else
			{
				printf("%d x %d = %2d   ", j, i, (i * j));
			}
		}
		printf("\n");
	}

	return 0;
}