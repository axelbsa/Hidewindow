#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIN32_LEAN_AND_MEAN

int main(int argc, char **argv)
{
	BOOL hotKey = FALSE;
	ATOM hide_hotKeyID;
	ATOM close_hotKeyID;
    HWND handle;
	HWND this;
	MSG msg = {0};
	
	char caption[200];
	char wndtext[200];
	
	if ((this = GetForegroundWindow()) != NULL )
	{
		ShowWindow(this,SW_HIDE);
		MessageBox(this,"Hider er klar","Main window",MB_OK|MB_ICONINFORMATION|MB_TASKMODAL);
	}
	
	hide_hotKeyID = GlobalAddAtom("hiderandomwindow");
	if (RegisterHotKey(NULL,hide_hotKeyID,MOD_ALT,0x48))
    {
		//printf("Hotkey 'ALT+h' registered, using MOD_NOREPEAT flag\n");
		//MessageBox(this,"Hotkey 'ALT+h' registered, using MOD_NOREPEAT flag\n","Main window handle",0);
	}
	
	close_hotKeyID = GlobalAddAtom("closeMainApp");
	if (RegisterHotKey(NULL,close_hotKeyID,MOD_ALT,0x51))
    {
		//printf("Hotkey 'ALT+q' registered, using MOD_NOREPEAT flag\n");
		//MessageBox(this,"Hotkey 'ALT+h' registered, using MOD_NOREPEAT flag\n","Main window handle",0);
	}
	
	while(1)
	{
		if (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				if (msg.wParam == close_hotKeyID)
				{
					if (hotKey)
						ShowWindow(handle,SW_SHOW);
					MessageBox(this,"Hider avsluttes","Main window handle",MB_OK|MB_ICONINFORMATION|MB_TASKMODAL);
					break;
				}
				else if (msg.wParam == hide_hotKeyID)
				{
					if (!hotKey)
					{
						handle = GetForegroundWindow();
						if (GetWindowText(handle,wndtext,100))
							printf("%s\n",wndtext);
						ShowWindow(handle,SW_HIDE);
						hotKey = TRUE;
					}
					else
					{
						ShowWindow(handle,SW_SHOW);
						hotKey = FALSE;
						handle = NULL;
						memset(wndtext,0,sizeof(wndtext));
					}
				}
			}
		}
	}
    return EXIT_SUCCESS;
}