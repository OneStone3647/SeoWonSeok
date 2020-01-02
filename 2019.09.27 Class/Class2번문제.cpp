#include <iostream>
#include <Windows.h>
using namespace std;

class Quad
{
private:
	int width;
	int height;
public:
	bool SetSize(int _width, int _height);
	void Draw();
};

bool Quad::SetSize(int _width, int _height)
{
	width = _width;
	height = _height;

	if (width < 1 || height < 1)
	{
		cout << "���� �Ǵ� ���ΰ� 1���� �۽��ϴ�." << endl;
		system("pause");
		return false;
	}
	else
	{
		return true;
	}
}

void Quad::Draw()
{
	for (int y = 1; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
			if (y == 1 && x == 1)
			{
				cout << "��";
			}
			else if ((y == 1 || y == height) && (x > 1 && x < width))
			{
				cout << "��";
			}
			else if (y == 1 && x == width)
			{
				cout << "��";
			}
			else if ((x == 1 || x == width) && (y > 1 && y < height))
			{
				cout << "��";
			}
			else if (x == 1 && y == height)
			{
				cout << "��";
			}
			else if (x == width && y == height)
			{
				cout << "��";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void main()
{
	Quad Qu;
	int width, height;
	while (1)
	{
		cout << "���� �Է� : ";
		cin >> width;
		cout << "���� �� �Է� : ";
		cin >> height;
		
		if (Qu.SetSize(width, height))
		{
			Qu.Draw();
			return;
		}
	}
}
