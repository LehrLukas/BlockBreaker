#include "Game.h"
#include "Windows.h"


Game::Game()
{
}


Game::~Game()
{
}

int Game::Run()
{
	CreateMainWindow();
	while (true)
	{

	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Game::CreateMainWindow()
{
	const char* ClassName = "BlockBreaker";
	HINSTANCE hInstance = GetModuleHandle(0);

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = 0; // LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = ClassName;
	wcex.hIconSm = 0;

	// if there is an icon, load it
	wcex.hIcon = (HICON)LoadImage(hInstance, __TEXT("irrlicht.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	RegisterClassEx(&wcex);

	// calculate client size

	RECT clientSize;
	clientSize.top = 0;
	clientSize.left = 0;
	clientSize.right = 640;
	clientSize.bottom = 480;

	DWORD style = WS_POPUP;

	bool fullScreen = false;

	if (!fullScreen)
		style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	AdjustWindowRect(&clientSize, style, FALSE);

	const int realWidth = clientSize.right - clientSize.left;
	const int realHeight = clientSize.bottom - clientSize.top;

	int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
	int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

	if (windowLeft < 0)
		windowLeft = 0;
	if (windowTop < 0)
		windowTop = 0;	// make sure window menus are in screen on creation

	if (fullScreen)
	{
		windowLeft = 0;
		windowTop = 0;
	}

	// create window

	HWND HWnd = CreateWindow(ClassName, __TEXT(""), style, windowLeft, windowTop,
		realWidth, realHeight, NULL, NULL, hInstance, NULL);
	//		CreationParams.WindowSize.Width = realWidth;
	//		CreationParams.WindowSize.Height = realHeight;

	ShowWindow(HWnd, SW_SHOWNORMAL);
	UpdateWindow(HWnd);

	// fix ugly ATI driver bugs. Thanks to ariaci
	MoveWindow(HWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);
	return false;
}

