#include <winsock2.h>
#include <stdio.h>

int main()
{
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	u_short x1 = 0x1234;
	u_long	y1 = 0x12345678;
	u_short x2;
	u_long	y2;

	//호스트바이트 -> 네트워크 바이트
	printf("[호스트 바이트 -> 네트워크 바잍트]\n");
	printf("0x%x -> 0x%x\n", x1, x2 = htons(x1));
	printf("0x%x -> 0x%x\n", y1, y2 = htonl(y1));

	//네트워크바이트 -> 호스트 바이트
	printf("\n[호스트 바이트 -> 네트워크 바잍트]\n");
	printf("0x%x -> 0x%x\n", x2, x1 = ntohs(x1));
	printf("0x%x -> 0x%x\n", y2, y1 = ntohl(y1));

	//잘못된 사용 예
	printf("\n[잘못된 사용 예]\n");
	printf("0x%x -> 0x%x\n", x1, ntohs(x1));

	WSACleanup();
	system("pause");

	return 0;
}