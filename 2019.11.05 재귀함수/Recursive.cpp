#include <iostream>
#include <Windows.h>

using namespace std;

int Sum(int n)
{
	if (n <= 0)
		return 0;
	return n + Sum(n - 1);
}

void Binary(int n)
{
	int na = 0;

	if (n > 1)
	{
		na = n % 2;
		Binary(n / 2);
		cout << na;
	}
	else
	{
		cout << n;
	}
}

void main()
{
	int Num1, Num2;
	cout << "1.정수 입력 : ";
	cin >> Num1;
	cout << "1 ~ " << Num1 << " : " << Sum(Num1) << endl;

	cout << "2.정수 입력 : ";
	cin >> Num2;
	cout << Num2 << " -> ";
	Binary(Num2);
}