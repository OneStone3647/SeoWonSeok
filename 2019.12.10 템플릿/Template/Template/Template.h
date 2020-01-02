#pragma once
#include <iostream>
using namespace std;

class Template
{
public:
	Template();
	// ���� �� 1����
	template <typename num>
	void PlusFunc(num n1);
	// �� �� �Է� �ּҰ�
	template <typename num1, typename num2>
	void MinNum(num1 n1, num2 n2);
	// �� �� �Է� �ִ밪
	template <typename num1, typename num2, typename num3>
	void MaxNum(num1, num2, num3);
	~Template();
};

template<typename num>
inline void Template::PlusFunc(num n1)
{
	int tmp = 1;
	n1 += tmp;
	cout << n1 << endl;
}

template<typename num1, typename num2>
inline void Template::MinNum(num1 n1, num2 n2)
{
	if (n1 <= n2)
	{
		cout << "�ּҰ� : " << n1 << endl;
	}
	else
	{
		cout << "�ּҰ� : " << n2 << endl;
	}
}

template<typename num1, typename num2, typename num3>
inline void Template::MaxNum(num1 n1, num2 n2, num3 n3)
{
	if (n1 >= n2)
	{
		if (n3 > n1)
		{
			cout << "�ִ밪 : " << n3 << endl;
		}
		else
		{
			cout << "�ִ밪 : " << n1 << endl;
		}
	}
	else
	{
		if (n3 > n2)
		{
			cout << "�ִ밪 : " << n3 << endl;
		}
		else
		{
			cout << "�ִ밪 : " << n2 << endl;
		}
	}

}
