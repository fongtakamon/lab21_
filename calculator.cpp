#include <windows.h>
#include <stdio.h>

double x;
double y;
char t[100];
char textSaved1[100];
char textSaved2[100];

char szClassName[] = "TextEntry";  

HWND textfield, buttonP, buttonD, buttonM, buttonH, TextBox1, TextBox2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
			textfield = CreateWindow("STATIC","Please input two numbers", WS_VISIBLE | WS_CHILD, 10, 10, 220, 30, hwnd, NULL, NULL, NULL);
			buttonP = CreateWindow("Button", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 60, 125, 25, 25, hwnd, (HMENU) 1, NULL, NULL);
			buttonD= CreateWindow("Button", "-", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 125, 25, 25, hwnd, (HMENU) 2, NULL, NULL);
			buttonM = CreateWindow("Button", "*", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 125, 25, 25, hwnd, (HMENU) 3, NULL, NULL);
			buttonH = CreateWindow("Button", "/", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 125, 25, 25, hwnd, (HMENU) 4, NULL, NULL);
			TextBox1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 40, 50, 160, 30, hwnd, NULL, NULL, NULL);
			TextBox2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 40, 80, 160, 30, hwnd, NULL, NULL, NULL);
			break;

		case WM_COMMAND:
			GetWindowText(TextBox1, &textSaved1[0], 100);
			GetWindowText(TextBox2, &textSaved2[0], 100);
			x = atof(textSaved1);
			y = atof(textSaved2);
			switch (LOWORD(wParam))
			{
				case 1:
					sprintf(t, "%f", x + y);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd, t, "Result", MB_OK);
					break;
				case 2:
					sprintf(t, "%f", x - y);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd, t, "Result", MB_OK);
					break;
				case 3:
					sprintf(t, "%f", x * y);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd, t, "Result", MB_OK);
					break;
				case 4:
					sprintf(t, "%f", x / y);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd, t, "Result", MB_OK);
					break;
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd; 
	MSG msg; 

	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = CreateSolidBrush(RGB(255, 182, 193));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		250, 
		200, 
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	while(GetMessage(&msg, NULL, 0, 0) > 0) { 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}