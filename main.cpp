#include <windows.h>

enum { id_button1 = 1, id_button2 };


void OnCreate(HWND hw) {
	
	 CreateWindow("BUTTON", "one", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 40, 50, 20, hw, (HMENU)id_button1, 0, 0);
	
	 CreateWindow("Button", "two", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 70, 50, 20, hw, (HMENU)id_button2, 0, 0);
}

void OnCommand(HWND hw, int id) {
	
	switch (id)
	{
		case id_button1:
			MessageBox(hw, "one", "NWP", MB_OK | WS_VISIBLE | MB_ICONEXCLAMATION | WS_CHILD);
			break;
		case id_button2:
			MessageBox(hw, "two", "NWP", MB_OK | WS_VISIBLE | MB_ICONEXCLAMATION | WS_CHILD);
			break;
	}
	
	
	
}

void OnDestroy() {
	PostQuitMessage(0);
}

LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
			OnCreate(hw);
			return 0;
		case WM_COMMAND:
			OnCommand(hw, LOWORD(wp));
			return 0;
		case WM_DESTROY:
			OnDestroy();
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}


int RegisterMyClass(HINSTANCE hInstance, char* className)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0,255,255));

	return RegisterClass(&wc);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	char clsName[] = "NWPClass";

	if(!RegisterMyClass(hInstance, clsName))
		return 0;

	HWND hwnd = CreateWindow(clsName, "NWP 1",  WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
		NULL, NULL, hInstance, NULL); 

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return msg.wParam;
}
