#include <windows.h>
#include <stdio.h>

#define MAXCNT 100000000

int g_count = 0;

//임계영역을 주지 않고 동기화 되지 않은 상태로 실행하면 실행 할때마다 다른 결과를 나타내게 될것이다.
//그 부분을 이해하고 임계영역을 활성화해서 실행했을때 항상 올바른값 0을 출력하는지 확인하고 이해해보자.

//주석 처리한 부분은 임계영역 코딩부분
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++)
	{
		EnterCriticalSection(&cs);
		g_count += 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++)
	{
		EnterCriticalSection(&cs);
		g_count -= 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	//임계영역 초기화
	InitializeCriticalSection(&cs);

	//Thread 두 개 생성
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);

	//Thread 두 개 종료 대기
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//임계영역 삭제
	DeleteCriticalSection(&cs);

	//결과 출력
	printf("g_count = %d\n", g_count);
	return 0;
}