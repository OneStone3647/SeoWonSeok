#include <iostream>
#include <Windows.h>
using namespace std;

class Gugu
{
private:
	int startDan;
	int endDan;
public:
	bool SetDan(int _startDan, int _endDan);
	void ShowDan();
};

bool Gugu::SetDan(int _startDan, int _endDan)
{
	startDan = _startDan;
	endDan = _endDan;

	if (startDan < 2 || startDan > 9)
	{
		cout << "���� ���� 2���� �۰ų� 9���� Ů�ϴ�." << endl;
		system("pause");
		return false;
	}
	else if (endDan < 2 || endDan > 9)
	{
		cout << "�� ���� 2���� �۰ų� 9���� Ů�ϴ�." << endl;
		system("pause");
		return false;
	}
	else
	{
		return true;
	}
}

void Gugu::ShowDan()
{
	for (int i = 0; i <= 9; i++)
	{
		for (int j = startDan; j <= endDan; j++)
		{
			if (i == 0)
			{
				cout << "=====" << j << "��=====" << '\t';
			}
			else
			{
				cout << j << " x " << i << " = " << i * j << '\t';
			}
		}
		cout << endl;
	}
}

void main()
{
	Gugu Gu;
	int startDan, endDan;
	while (1)
	{
		cout << "���� �� �Է� : ";
		cin >> startDan;
		cout << "�� �� �Է� : ";
		cin >> endDan;

		if (Gu.SetDan(startDan, endDan))
		{
			Gu.ShowDan();
			return;
		}
	}
}