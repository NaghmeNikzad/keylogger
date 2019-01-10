#include <Windows.h>

SOCKET connectToServer();
bool checkConnection(SOCKET sock);
bool sendMessage(SOCKET ConnectSocket, char* message);