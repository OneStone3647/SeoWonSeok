#include <stdio.h>
#include <string.h>

//int main()
//{	
//	//char Name[10];
//	//char My_Name[10] = "JungHo";
//
//	//strcpy(Name, My_Name);
//	//printf("Name : %s\n", Name);
//	//printf("My_Name: %s\n", My_Name);
//
//	return 0;
//}

int Strlen(const char *str)
{
	int count = 0;

	while (str[count] != '\0')
	{
		count++;
	}

	return count;
}

char* Strcpy(char *Name, const char *My_Name)
{
	int count = 0;

	while (My_Name[count] != '\0')
	{
		Name[count] = My_Name[count];
		count++;
	}
	Name[count] = '\0';

	return Name;
}

char* Strcat(char *str, const char *str_temp)
{
	int count = 0;
	int count_temp = 0;

	while (str[count] != '\0')
	{
		count++;
	}

	while (str_temp[count_temp] != '\0')
	{
		str[count] = str_temp[count_temp];
		count++;
		count_temp++;
	}
	str[count] = '\0';

	return str;
}

int Strcmp(const char *str1,  const char *str2)
{
	int count = 0;

	while (1)
	{
		if (str1[count] > str2[count])
		{
			return 1;
		}
		else if (str1[count] < str2[count])
		{
			return -1;
		}
		else if (str1[count] == NULL && str2[count] == NULL)
		{
			return 0;
		}

		count++;
	}
}

int main()
{
	//char str[100];
	//printf("문자열 입력: ");
	//scanf("%s", &str);	
	//printf("%s 문자열의 길이: %d\n", str, Strlen(str));

	//char Name[10];
	//char My_Name[10] = "JungHo";
	//Strcpy(Name, My_Name);
	//printf("Name: %s\n", Name);
	//printf("My_Name: %s\n", My_Name);

	//char str[10] = "Hello";
	//printf("%s\n", str);
	//Strcat(str, "^^");
	//printf("%s\n", str);	

	char str1[10] = "string!!";
	char str2[10] = "string";

	printf("%s == %s : %d\n", str1, str2, Strcmp(str1, str2));
	printf("%s == %s : %d\n", "abc", "abc", Strcmp("abc", "abc"));
	printf("%s == %s : %d\n", "abc", "def", Strcmp("abc", "def"));


	return 0;
}