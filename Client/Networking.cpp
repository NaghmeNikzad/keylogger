#include "Definitions.h"
#include "Configs.h"
#include "Utils.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

SOCKET connectToServer() {

	log("Connecting to server...");

	// Initialize Needed Vars
	WSADATA wsaData;
	int iResult;
	char log_msg[1024];

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		sprintf(log_msg, "WSAStartup failed: (error: %ld)", iResult);
		log(log_msg);
		return INVALID_SOCKET;
	}

	struct addrinfo *result = NULL,
                *ptr = NULL,
                hints;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;


	// Resolve the server address and port
	iResult = getaddrinfo(SERVER_IP_ADDRESS, SERVER_CONECCTION_PORT, &hints, &result);
	if (iResult != 0) {
		sprintf(log_msg, "getaddrinfo failed: (error: %ld)", iResult);
		log(log_msg);
		WSACleanup();
		return INVALID_SOCKET;
	}

	
	SOCKET ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr=result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
		ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		sprintf(log_msg, "Error at socket(): (error: %ld)", WSAGetLastError());
		log(log_msg);
		freeaddrinfo(result);
		WSACleanup();
		return INVALID_SOCKET;
	}

	// Connect to server.
	iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		sprintf(log_msg, "Unable connect to server! (error: %ld)", WSAGetLastError());
		log(log_msg);
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		return INVALID_SOCKET;
	}
	
	
	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		sprintf(log_msg, "Unable connect to server! %ld", WSAGetLastError());
		log(log_msg);
		WSACleanup();
		return INVALID_SOCKET;
	}
	
	log("Connected successfully to server.");
	return ConnectSocket;
}


bool sendMessage(SOCKET ConnectSocket, char* message) {

	char sendbuf[1024];

	strcpy(sendbuf, message);
	strcat(sendbuf, "<EOF>\n");

	int iResult;

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		 //printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return false;
	}

	// printf("Bytes Sent: %ld\n", iResult);
	
	return true;
}

bool checkConnection(SOCKET sock) {

	char buff[16] = "check<EOF>\n";
	
	int res  = send(sock, buff, (int) strlen(buff), 0);
	int res2 = WSAGetLastError();
	int ret = recv(sock, buff, sizeof(buff)/sizeof(char) - 1, 0);
	if ( ret == SOCKET_ERROR ) 
	{
		log("Disconnected!");
		closesocket(sock);
		WSACleanup();
		return false;
	}

	return true;
}