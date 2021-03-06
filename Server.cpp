// Server.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include<iostream>
#include<Winsock2.h>
#include<stdio.h>
#include<conio.h>
#pragma comment(lib,"Ws2_32")
using namespace std;
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048

int main(){
	//tao winsock

	WSADATA wsaData;

	WORD WVersion = MAKEWORD(2, 2);

	if (WSAStartup(WVersion, &wsaData))

		cout << "Version is not supported" << endl;

	SOCKET listenSock;
	
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(SERVER_PORT);

	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr))) {

		cout << "Error! Cannot bind this address." << endl;
		_getch();
		return 0;
	}

	if (listen(listenSock, 10)) {

		cout << "Error, Cannot listen.";

		_getch();
		
		return 0;
	}

	cout << "Server da hoat dong" << endl;

	sockaddr_in clientAddr;
	
	char buff[BUFF_SIZE];

	int ret,clientAddrLen = sizeof(clientAddr);

	while (1) {

		SOCKET connSock;

		connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);

		ret = recv(connSock, buff, BUFF_SIZE, 0);

		if (ret == SOCKET_ERROR) {

			cout << "ERROR:" << WSAGetLastError();

			break;
		}

		else if (strlen(buff) > 0) {

			buff[ret] = 0;

			cout << " Rececive from client " << inet_ntoa(clientAddr.sin_addr) << "  " << ntohs(clientAddr.sin_port) << "  " << buff << endl;

			ret = send(connSock, buff, strlen(buff), 0);

			if (ret == SOCKET_ERROR);

			cout << "ERROR:" << WSAGetLastError();


		}

		closesocket(connSock);

	}

	closesocket(listenSock);

	WSACleanup();

	return 0;


}
