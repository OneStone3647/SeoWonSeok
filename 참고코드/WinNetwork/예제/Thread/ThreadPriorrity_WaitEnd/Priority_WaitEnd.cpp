#include <Windows.h>
#include <stdio.h>

//DWORD WINAPI MyThread(LPVOID arg)
//{
//	while (1);
//	return 0;
//}
//
//int main()
//{
//	//CPU 개수를 알아낸다.
//	SYSTEM_INFO si;
//	GetSystemInfo(&si);
//
//	//CPU 개수만큼 Thread를 생성한다.
//	for (int i = 0; i < (int)si.dwNumberOfProcessors; i++)
//	{
//		HANDLE hThread = CreateThread(NULL, 0, MyThread, NULL, 0, NULL);
//		
//		if (hThread == NULL)
//			return 1;
//
//		//최고 우선순위로 변경한다.
//		SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL); //해당 옵션에 대해 더 알아보자!!
//		CloseHandle(hThread);
//	}
//
//	Sleep(1000);
//
//	while (1) 
//	{ 
//		printf("Main Thread 실행!\n");
//		break;
//	}
//
//	return 0;
//}

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg)
{
	int num = (int)arg;
	
	for (int i = 1; i <= num; i++)
		sum += i;

	return 0;
}

int main()
{
	int num = 100;

	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL);

	if (hThread == NULL)
		return 1;

	printf("Thread 실행 전, 계산 결과 = %d\n", sum);

	ResumeThread(hThread);

	WaitForSingleObject(hThread, INFINITE);

	printf("Thread 실행 후, 계산 결과 = %d\n", sum);

	CloseHandle(hThread);

	return 0;
}