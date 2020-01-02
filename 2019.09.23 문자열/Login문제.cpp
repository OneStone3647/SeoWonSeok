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
	// 영어랑 숫자만 가능 아닐 경우 false
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
			cout << "동일한 아이디가 존재합니다." << endl;
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
		cout << "아이디 입력([3글자↑] AND [한글X]) : ";
		cin >> member[index].id;

		//EnglishCheck(member[index].id, &englishCheck);
		if (!EnglishCheck(member[index].id))
		{
			cout << "id가 영문이 아닙니다." << endl;
		}

		//LengthCheck(member[index].id, &lengthCheck, 3);
		if (!LengthCheck(member[index].id, 3))
		{
			cout << "id가 세글자 이하 입니다." << endl;
		}

		// 처음 입력할 경우
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
			//처음 이후 입력할 경우
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
		cout << "비밀번호 입력([8글자↑] AND [숫자 포함]) : ";
		cin >> member[index].password;
		cout << "비밀번호 확인 : ";
		cin >> temp;

		//EnglishCheck(member[index].password, &englishCheck);
		if (!EnglishCheck(member[index].password))
		{
			cout << "password가 영문이 아닙니다." << endl;
		}

		//LengthCheck(member[index].password, &lengthCheck, 8);
		if (!LengthCheck(member[index].password, 8))
		{
			cout << "password가 여덟글자 이하 입니다." << endl;
		}

		//NumberCheck(member[index].password, &numCheck);
		if (!NumberCheck(member[index].password))
		{
			cout << "숫자가 포함되어 있지 않습니다." << endl;
		}

		//PWSameCheck(member[index].password, temp, &sameCheck);
		if (!PWSameCheck(member[index].password, temp))
		{
			cout << "비밀번호가 일치하지 않습니다." << endl;
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
	cout << "닉네임 입력 : ";
	cin >> member[index].name;
	cout << "나이 입력 : ";
	cin >> member[index].age;
	cout << "휴대폰 번호 입력 : ";
	cin >> member[index].phoneNum;
	cout << "회원가입 성공 !! 마일리지 1000원 등록" << endl;
	member[index].mileage += 1000;			// 초기화 하지 않으면 값이 들어가지 않음
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
			cout << "비밀번호가 틀렸습니다." << endl;
			system("pause");
			return false;
		}
	}
}

void ShowInfo(Info* member, int index)
{
	system("cls");
	cout << "============회원 정보============" << endl;
	cout << "ID : " << member[index].id << '\t' << "닉네임 : " << member[index].name << endl;
	cout << "나이 : " << member[index].age << "살" << '\t' << "휴대폰 번호 : " << member[index].phoneNum << endl;
	cout << "마일리지 : " << member[index].mileage << "원" << endl;
}

void Login(Info* member, int index, int* loginIndex, bool* loginSuccess)
{
	string tempID, tempPW;
	bool idCheck;
	bool pwCheck;

	while (1)
	{
		system("cls");
		cout << "아이디 입력 : ";
		cin >> tempID;
		cout << "비밀번호 입력 : ";
		cin >> tempPW;

		//CheckID(tempID, member, index, &idCheck);
		// 아이디 일치시 비밀번호 확인
		if (CheckID(tempID, member, index))
		{
			//CheckPW(tempPW, member, index, &pwCheck);
			CheckPW(tempPW, member, index);
		}
		else
		{
			cout << "해당 아이디가 없습니다." << endl;
			system("pause");
		}

		// 아이디, 비밀번호 모두 일치
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
		cout << "1.닉네임 변경" << endl;
		cout << "2.나이 변경" << endl;
		cout << "3.휴대폰 번호 변경" << endl;
		cout << "4.돌아가기" << endl;
		cout << "입력 : ";
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "현재 닉네임 : " << member[index].name << endl;
			cout << "변경할 닉네임입력 : ";
			cin >> tempStr;
			cout << member[index].name << "->" << tempStr << endl;
			member[index].name = tempStr;
			system("pause");
			break;
		case 2:
			cout << "현재 나이 : " << member[index].age << endl;
			cout << "변경할 나이입력 : ";
			cin >> tempNum;
			cout << member[index].age << "->" << tempNum << endl;
			member[index].age = tempNum;
			system("pause");
			break;
		case 3:
			cout << "현재 휴대폰 번호 : " << member[index].phoneNum << endl;
			cout << "변경할 휴대폰 번호입력 : ";
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
		cout << "1.회원 정보" << endl;
		cout << "2.회원 정보 변경" << endl;
		cout << "3.로그아웃" << endl;
		cout << "입력 : ";
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
		cout << "=====Login=====(회원수[" << index << "명])" << endl;
		cout << "1.회원 가입" << endl;
		cout << "2.로그인" << endl;
		cout << "3.종료" << endl;
		cout << "입력 : ";
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
				cout << "더이상 회원을 등록할 수 없습니다." << endl;
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