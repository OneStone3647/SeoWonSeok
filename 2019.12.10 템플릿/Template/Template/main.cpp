#include "Template.h"

void main()
{
	
	Template temp;
	cout << "1. 1증가 템플릿" << endl;
	temp.PlusFunc(10.5);
	cout << "2. 두 수 입력 : ";
	int num1;
	float num2;
	cin >> num1;
	cin >> num2;
	temp.MinNum(num1, num2);
	int num3;
	float num4;
	char num5;
	cout << "3. 세 수 입력 : ";
	cin >> num3;
	cin >> num4;
	cin >> num5;
	temp.MaxNum(num3, num4, num5);
}