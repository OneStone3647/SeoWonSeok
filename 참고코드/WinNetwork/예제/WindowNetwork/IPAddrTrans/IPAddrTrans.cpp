#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int main()
{
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}

	/*------------------*/
	/*   IPv4 변환연습   */
	/*------------------*/
	//원래의 IPv4 주소출력
	const char *ipv4test = "147.46.114.70";
	printf("IPv4 주소(변환 전) = %s\n", ipv4test);

	//inet_addr() 함수연습
	printf("IPv4 주소(변환 후) = 0x%x\n", inet_addr(ipv4test));

	//inet_ntoa() 함수연습
	IN_ADDR ipv4num;
	ipv4num.s_addr = inet_addr(ipv4test);
	printf("IPv4 주소(다시 변환 후) = %s\n", inet_ntoa(ipv4num));

	printf("\n");
	system("pause");

	WSACleanup();

	return 0;
}