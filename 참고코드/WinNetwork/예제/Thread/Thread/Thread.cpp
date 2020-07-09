#include <Windows.h>
#include <stdio.h>
//#include <process.h> //C/C++ 라이브러리를 사용하는 Thread 생성 종료 함수 사용할때 필요!!

struct Point3D
{
	int x, y, z;
};

DWORD WINAPI MyThread(LPVOID arg)
//unsigned __stdcall MyThread(LPVOID arg) //C/C++ 라이브러리를 사용하는 Thread 함수
{
	Point3D *pt = (Point3D*)arg;

	//1초마다 ThreadID와 x, y, z를 호출한다.
	while (1)
	{
		printf("Running MyThread() %d : %d, %d, %d\n",
			GetCurrentThreadId(), pt->x, pt->y, pt->z);

		Sleep(1000);
	}

	//종료 코드 생략가능
	ExitThread(0);
	//_endthreadex(0); //C/C++ 라이브러리를 사용하는 Thread 종료 함수

	return 0;
}

int main(int argc, char* argv[])
{
	//첫 번째 Thread 생성
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	//HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, MyThread, &pt1, 0, NULL); //C/C++ 라이브러리를 사용하는 Thread 생성 함수

	if (hThread1 == NULL)
		return 1;

	CloseHandle(hThread1);

	//두 번째 Thread 생성
	Point3D pt2 = { 40, 50, 60 };
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	//HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, MyThread, &pt2, 0, NULL); //C/C++ 라이브러리를 사용하는 Thread 생성 함수

	if (hThread2 == NULL)
		return 1;

	CloseHandle(hThread2);

	//Main Thread를 매초마다 ThreadID를 출력한다.
	while (1)
	{
		printf("Running main() %d\n", GetCurrentThreadId());
		Sleep(1000);
	}

	return 0;
}