// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<conio.h>
#include<iostream>
#include<Winsock2.h>
#include<stdio.h>
#pragma comment(lib,"Ws2_32")
using namespace std;
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
int main() {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	
	if (WSAStartup(wVersion, &wsaData)) 
		
		cout << "Version is not support\n";

		SOCKET client;

		client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		int tv = 10000;

		setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));

		sockaddr_in serverAddr;

		serverAddr.sin_family = AF_INET;

		serverAddr.sin_port = htons(SERVER_PORT);

		serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

		if (connect(client, (sockaddr *)&serverAddr, sizeof(serverAddr))) {

			cout << "ERROR! Cannot connect server " << WSAGetLastError() << endl;

			_getch();

			return 0;
		}

		cout << "Connected server!\n";

		char buff[BUFF_SIZE];

		int ret;

		cout << " Send to server: ";

		gets_s(buff, BUFF_SIZE);

		ret = send(client, buff, strlen(buff), 0);

		if (ret == SOCKET_ERROR)

			cout << "ERROR! cannot send message";

		ret = recv(client, buff, BUFF_SIZE, 0);

		if (ret == SOCKET_ERROR) {

			if (WSAGetLastError() == WSAETIMEDOUT)

				cout << "TIME-out";

			else

				cout << "ERROR! Cannot receive message.";


		}
		
		else if (strlen(buff) > 0) {

			buff[ret] = 0;
			
			printf("Receive form server[%s:%d] %s\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port), buff);


		}

		closesocket(client);

		WSACleanup();

		_getch();

	return 0;

		
	
	
}