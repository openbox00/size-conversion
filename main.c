#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <tchar.h>    //string and other mapping macros
#include <string.h>

char textSaved1[10];
char textSaved2[10];
char textSaved3[10];

char value1[10];
char value2[10];

HWND TextBox1;
HWND TextBox2;
HWND TextBox3;
HWND TextField1;
HWND TextField2;
HWND TextField3;
HWND TextField4;
HWND TextField5;
HWND List1;
HWND List2;

enum {
  IDBC_DEFPUSHBUTTON=200,
  IDBC_PUSHBUTTON,
  IDBC_AUTOCHECKBOX,
  IDBC_AUTORADIOBUTTON,
  IDBC_GROUPBOX,
  IDBC_ICON,
  IDBC_BITMAP
};

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
					
		case WM_CREATE: {
			TextField1 =	CreateWindow("STATIC",
						"長度",
						WS_CHILD | WS_VISIBLE,
						20, 0, 32, 20,
						hwnd, NULL, NULL, NULL);			
			TextBox1 =	CreateWindow("EDIT",
						"2",
						WS_BORDER | WS_CHILD | WS_VISIBLE,
						20, 20, 110, 20,
						hwnd, NULL, NULL, NULL);
			TextField4 =	CreateWindow("STATIC",
						"單位",
						WS_CHILD | WS_VISIBLE,
						150, 0, 32, 20,
						hwnd, NULL, NULL, NULL);				
			List1  	 = 	CreateWindow("LISTBOX",
						"",
						 WS_CHILD | WS_BORDER | WS_VISIBLE | LBS_HASSTRINGS | LBS_NOTIFY |  LBS_NOINTEGRALHEIGHT,
						150, 20, 30, 35,
						hwnd, (HMENU)105, NULL, NULL);	
			SendMessage(List1, LB_ADDSTRING   , 0, (LPARAM) "mm");
    		SendMessage(List1, LB_ADDSTRING   , 0, (LPARAM) "呎");	    		
    		SendMessage(List1, LB_SETCURSEL, (WPARAM)0, 0);
														
			TextField2 =	CreateWindow("STATIC",
						"寬度",
						WS_CHILD | WS_VISIBLE,
						20, 60, 32, 20,
						hwnd, NULL, NULL, NULL);			
			TextBox2 = 	CreateWindow("EDIT",
						"3",
						WS_BORDER | WS_CHILD | WS_VISIBLE,
						20, 80, 110, 20,
						hwnd, NULL, NULL, NULL);	
			TextField5 =	CreateWindow("STATIC",
						"單位",
						WS_CHILD | WS_VISIBLE,
						150, 60, 32, 20,
						hwnd, NULL, NULL, NULL);						
			List2	 = 	CreateWindow("LISTBOX",
						"",
						 WS_CHILD | WS_BORDER | WS_VISIBLE | LBS_HASSTRINGS | LBS_NOTIFY |  LBS_NOINTEGRALHEIGHT,
						150, 80, 30, 35,
						hwnd, (HMENU)106, NULL, NULL);	
			SendMessage(List2, LB_ADDSTRING, 0, (LPARAM) "mm");
    		SendMessage(List2, LB_ADDSTRING, 0, (LPARAM) "呎");
    		SendMessage(List2, LB_SETCURSEL, (WPARAM)0, 0);
															
			TextField3 =	CreateWindow("STATIC",
						"單價",
						WS_CHILD | WS_VISIBLE,
						20, 110, 32, 20,
						hwnd, NULL, NULL, NULL);						
			TextBox3 = 	CreateWindow("EDIT",
						"4",
						WS_BORDER | WS_CHILD | WS_VISIBLE,
						20, 130, 110, 20,
						hwnd, NULL, NULL, NULL);		
																	
						
			CreateWindow("BUTTON",
						"計算",
						WS_CHILD | WS_VISIBLE,
						220, 20, 50, 20,
						hwnd, (HMENU) 1, NULL, NULL);
			break;			
		}

						
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
				case 1 :{
					int a,b,c;
					
					a = GetWindowText(TextBox1, &textSaved1[0], 10);//10數字長度 
					b = GetWindowText(TextBox2, &textSaved2[0], 10);
					c = GetWindowText(TextBox3, &textSaved3[0], 10);	
				
					int d,e;					
							
					d= SendMessage(List1, LB_GETCURSEL, 0,0);
					e= SendMessage(List2, LB_GETCURSEL, 0,0);
					SendMessage(List1, LB_GETTEXT, (WPARAM)(int)(d),(LPARAM)(LPCTSTR)(value1));
					MessageBox(List1, value1, "長度單位", MB_OK);
					SendMessage(List2, LB_GETTEXT, (WPARAM)(int)(e),(LPARAM)(LPCTSTR)(value2));
					MessageBox(List2, value2, "寬度單位", MB_OK);					

					float width	; /* width */
					float height; /* height */
					float price	; /* 價錢 */					
					
					
					height 	= atof(textSaved2);
					width 	= atof(textSaved1);		
					price 	= atof(textSaved3);						
					
					
					if (!strcmp(value1,"mm")){
						height = height/303;
					}else{
						height = height;
					}	
									
				
					
					if (!strcmp(value2,"mm")){
						width = width/303;
					}else{
						width = width;
					}	

								
					float ans;
					
					ans = width * height * price;
					char buffer[50];
					
					ftoa(ans,buffer,2);
										
					MessageBeep(MB_ICONWARNING);
					MessageBox(hwnd, buffer, "總價", MB_OK);
			
					break;
				}		
									
			break;
		}
				
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","才數計算",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		320, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}


