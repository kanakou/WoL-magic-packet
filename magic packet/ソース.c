#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#define BROADCAST_ADDR "10.0.0.255"

int main(int argc, char* argv[])
{
	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;
	BOOL yes = 1;
	char buf[102];
	char mac[] = { 0x00, 0x00, 0x5e, 0x00, 0x53, 0x00 };	//mac address
	int err;

	/*if (argc < 2)
	{
		putchar('>');		scanf();
	}*/

	//mac = (char)strtol(argv[2], NULL, 16);

	err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	/*switch (err)
	{
	case 0:
		break;
	case WSASYSNOTREADY:
		
	}*/

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(9);
	inet_pton(AF_INET, BROADCAST_ADDR, &addr.sin_addr.S_un.S_addr);
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));

	for (int i = 0; i < 6; i++)
	{
		buf[i] = 0xff;
	}

	for (int i = 1; i < 17;i++)
	{
		memcpy(buf + i * 6, mac, 6);
	}

	
	sendto(sock, buf, 102, 0, (struct sockaddr*)&addr, sizeof(addr));

	closesocket(sock);

	WSACleanup();

	return 0;
}