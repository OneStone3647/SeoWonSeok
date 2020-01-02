#include <stdio.h>

void main()
{
	FILE* f = fopen("GoGoDan.txt", "w");
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 2; j <= 9; j++)
		{
			if (i == 0)
				fprintf(f, "====%d´Ü====\t", j);
			else
				fprintf(f, "%d x %d = %d\t", j, i, i*j);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}