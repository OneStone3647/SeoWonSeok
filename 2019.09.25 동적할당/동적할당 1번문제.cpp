#include <iostream>
#include <string>

#define MAX 5

using namespace std;

void Input(int* num)
{
	for (int i = 0; i < MAX; i++)
	{
		cout << i + 1  << "��° ���� : ";
		cin >> num[i];
	}
}

void ShowNum(int* num)
{
	cout << "====================" << endl;
	for (int i = 0; i < MAX; i++)
	{
		cout << i + 1 << "��° ���� : " << num[i] << endl;
	}
	cout << "====================" << endl;
}

void BubbleSort(int* num)
{
	int temp;
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX - i - 1; j++)
		{
			if (num[j] > num[j + 1])
			{
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
}



int main()
{
	int* num;
	num = new int[MAX];

	Input(num);
	cout << "�������� ������" << endl;
	ShowNum(num);
	BubbleSort(num);
	cout << "�������� ������" << endl;
	ShowNum(num);	

	return 0;
}