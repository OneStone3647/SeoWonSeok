#include <iostream>
#include <string>
#include <Windows.h>

#define MAX 10

using namespace std;

struct Info{
	string id;
	string password;
	string name;
	int age;
	int phoneNum;
	int mileage;
};

bool EnglishCheck(string str)
{
	// ����� ���ڸ� ���� �ƴ� ��� false
	for (int i = 0; i < str.length(); i++)
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')))
		{
			return false;
		}
	}
}

bool LengthCheck(string str, int length)
{
	if (str.length() < length)
	{
		return false;
	}
}

bool IDSameCheck(string str, Info* member, int index)
{
	for (int i = 0; i < index; i++)
	{
		string temp = member[i].id;
		if (str == temp)
		{
			cout << "������ ���̵� �����մϴ�." << endl;
			return false;
		}
	}
}

void SetID(Info* member, int index)
{
	int check;
	bool englishCheck;
	bool lengthCheck;
	bool sameCheck;

	while (1)
	{
		check = 0;

		system("cls");
		cout << "���̵� �Է�([3���ڡ�] AND [�ѱ�X]) : ";
		cin >> member[index].id;

		//EnglishCheck(member[index].id, &englishCheck);
		if (!EnglishCheck(member[index].id))
		{
			cout << "id�� ������ �ƴմϴ�." << endl;
		}

		//LengthCheck(member[index].id, &lengthCheck, 3);
		if (!LengthCheck(member[index].id, 3))
		{
			cout << "id�� ������ ���� �Դϴ�." << endl;
		}

		// ó�� �Է��� ���
		if (index != 0)
		{
			//IDSameCheck(member[index].id, member, index, &sameCheck);
			if (EnglishCheck(member[index].id) && LengthCheck(member[index].id, 3) && IDSameCheck(member[index].id, member, index))
			{
				break;
			}
			else
			{
				system("pause");
			}
		}
		else
			//ó�� ���� �Է��� ���
		{
			if (EnglishCheck(member[index].id) && LengthCheck(member[index].id, 3))
			{
				break;
			}
			else
			{
				system("pause");
			}
		}		
	}
}

bool NumberCheck(string str)
{
	int count = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
		{
			count += 1;
		}
	}

	if (count == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PWSameCheck(string str, string temp)
{
	if (str != temp)
	{
		return false;
	}
}

void SetPassword(Info* member, int index)
{
	string temp;
	bool englishCheck;
	bool lengthCheck;
	bool numCheck;
	bool sameCheck;

	while (1)
	{
		system("cls");
		cout << "��й�ȣ �Է�([8���ڡ�] AND [���� ����]) : ";
		cin >> member[index].password;
		cout << "��й�ȣ Ȯ�� : ";
		cin >> temp;

		//EnglishCheck(member[index].password, &englishCheck);
		if (!EnglishCheck(member[index].password))
		{
			cout << "password�� ������ �ƴմϴ�." << endl;
		}

		//LengthCheck(member[index].password, &lengthCheck, 8);
		if (!LengthCheck(member[index].password, 8))
		{
			cout << "password�� �������� ���� �Դϴ�." << endl;
		}

		//NumberCheck(member[index].password, &numCheck);
		if (!NumberCheck(member[index].password))
		{
			cout << "���ڰ� ���ԵǾ� ���� �ʽ��ϴ�." << endl;
		}

		//PWSameCheck(member[index].password, temp, &sameCheck);
		if (!PWSameCheck(member[index].password, temp))
		{
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
		}
		if (EnglishCheck(member[index].password) && LengthCheck(member[index].password, 8) 
			&& NumberCheck(member[index].password) && PWSameCheck(member[index].password, temp))
		{
			break;
		}
		else
		{
			system("pause");
		}
	}
}

void SetElse(Info* member, int index)
{
	system("cls");
	cout << "�г��� �Է� : ";
	cin >> member[index].name;
	cout << "���� �Է� : ";
	cin >> member[index].age;
	cout << "�޴��� ��ȣ �Է� : ";
	cin >> member[index].phoneNum;
	cout << "ȸ������ ���� !! ���ϸ��� 1000�� ���" << endl;
	member[index].mileage += 1000;			// �ʱ�ȭ ���� ������ ���� ���� ����
	system("pause");
}

bool CheckID(string str, Info* member, int index)
{
	for (int i = 0; i < index; i++)
	{
		string temp = member[i].id;
		if (str != temp)
		{
			return false;
		}
	}
}

bool CheckPW(string str, Info* member, int index)
{
	for (int i = 0; i < index; i++)
	{
		string temp = member[i].password;
		if (str != temp)
		{
			cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
			system("pause");
			return false;
		}
	}
}

void ShowInfo(Info* member, int index)
{
	system("cls");
	cout << "============ȸ�� ����============" << endl;
	cout << "ID : " << member[index].id << '\t' << "�г��� : " << member[index].name << endl;
	cout << "���� : " << member[index].age << "��" << '\t' << "�޴��� ��ȣ : " << member[index].phoneNum << endl;
	cout << "���ϸ��� : " << member[index].mileage << "��" << endl;
}

void Login(Info* member, int index, int* loginIndex, bool* loginSuccess)
{
	string tempID, tempPW;
	bool idCheck;
	bool pwCheck;

	while (1)
	{
		system("cls");
		cout << "���̵� �Է� : ";
		cin >> tempID;
		cout << "��й�ȣ �Է� : ";
		cin >> tempPW;

		//CheckID(tempID, member, index, &idCheck);
		// ���̵� ��ġ�� ��й�ȣ Ȯ��
		if (CheckID(tempID, member, index))
		{
			//CheckPW(tempPW, member, index, &pwCheck);
			CheckPW(tempPW, member, index);
		}
		else
		{
			cout << "�ش� ���̵� �����ϴ�." << endl;
			system("pause");
		}

		// ���̵�, ��й�ȣ ��� ��ġ
		if (CheckID(tempID, member, index) && CheckPW(tempPW, member, index))
		{
			(*loginIndex) = index - 1;
			(*loginSuccess) = true;
			break;
		}
	}
}

void ChangeInfo(Info*member, int index)
{
	int select = 0;
	string tempStr;
	int tempNum;

	while (1)
	{
		ShowInfo(member, index);

		cout << "===================" << endl;
		cout << "1.�г��� ����" << endl;
		cout << "2.���� ����" << endl;
		cout << "3.�޴��� ��ȣ ����" << endl;
		cout << "4.���ư���" << endl;
		cout << "�Է� : ";
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "���� �г��� : " << member[index].name << endl;
			cout << "������ �г����Է� : ";
			cin >> tempStr;
			cout << member[index].name << "->" << tempStr << endl;
			member[index].name = tempStr;
			system("pause");
			break;
		case 2:
			cout << "���� ���� : " << member[index].age << endl;
			cout << "������ �����Է� : ";
			cin >> tempNum;
			cout << member[index].age << "->" << tempNum << endl;
			member[index].age = tempNum;
			system("pause");
			break;
		case 3:
			cout << "���� �޴��� ��ȣ : " << member[index].phoneNum << endl;
			cout << "������ �޴��� ��ȣ�Է� : ";
			cin >> tempNum;
			cout << member[index].phoneNum << "->" << tempNum << endl;
			member[index].phoneNum = tempNum;
			system("pause");
			break;
		case 4:
			return;
		}
	}
}

void LoginMenu(Info* member, int index)
{
	int select = 0;

	while (1)
	{
		system("cls");
		cout << "========Menu========" << endl;
		cout << "1.ȸ�� ����" << endl;
		cout << "2.ȸ�� ���� ����" << endl;
		cout << "3.�α׾ƿ�" << endl;
		cout << "�Է� : ";
		cin >> select;

		switch (select)
		{
		case 1:
			ShowInfo(member, index);
			system("pause");
			break;
		case 2:
			ChangeInfo(member, index);
			break;
		case 3:
			return;
		}
	}
}

void main()
{
	Info member[10] = {};
	int index = 0;
	int select = 0;
	int loginIndex = 0;
	bool loginSuccess = false;

	while (1)
	{
		system("cls");
		cout << "=====Login=====(ȸ����[" << index << "��])" << endl;
		cout << "1.ȸ�� ����" << endl;
		cout << "2.�α���" << endl;
		cout << "3.����" << endl;
		cout << "�Է� : ";
		cin >> select;

		switch (select)
		{
		case 1:
			if (index < MAX)
			{
				SetID(member, index);
				SetPassword(member, index);
				SetElse(member, index);
				index++;
			}
			else
			{
				cout << "���̻� ȸ���� ����� �� �����ϴ�." << endl;
				system("pause");
			}
			break;
		case 2:
			system("cls");
			Login(member, index, &loginIndex, &loginSuccess);
			if (loginSuccess)
			{
				LoginMenu(member, loginIndex);
			}
			break;
		case 3:
			return;
		}
	}
	return;
}