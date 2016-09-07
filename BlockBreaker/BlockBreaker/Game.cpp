#include "Game.h"
#include "Windows.h"
#include <chrono>

Game::Game() :windowWidth(640), windowHeight(480), close(false), tickPerSecond(25), maxFrameLoss(5)
{
}

Game::~Game()
{
}

int Game::Run()
{
	CreateMainWindow();
	using std::chrono::high_resolution_clock;
	auto previous = high_resolution_clock::now();
	auto lag = previous - previous;
	auto nanoPerUpdate = std::chrono::nanoseconds(1000000000 / tickPerSecond);
	while (!close)
	{
		auto current = high_resolution_clock::now();
		auto elapsed = current - previous;
		previous = current;
		lag += elapsed;
		ProcessInput();
		while (lag >= nanoPerUpdate)
		{
			Update();
			lag -= nanoPerUpdate;
		}
		float interpolation = float(lag.count()) / float(nanoPerUpdate.count());
		Render(interpolation);

		/*int loops = 0;
		while (time.now() > nextTickTime && loops < maxFrameLoss)
		{
			Update();
			nextTickTime += milliSecondPerTick;
			loops++;
		}
		float interpolation = float(time.now() + milliSecondPerTick - nextTickTime) / float(milliSecondPerTick);
		Display(interpolation);*/

	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Game::CreateMainWindow()
{
	const wchar_t* ClassName = L"BlockBreaker";
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
	clientSize.right = windowWidth;
	clientSize.bottom = windowHeight;

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

	SetActiveWindow(HWnd);
	SetForegroundWindow(HWnd);
	return false;
}

void Game::ProcessInput()
{
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// No message translation because we don't use WM_CHAR and it would conflict with our
		// deadkey handling.
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			close = true;
	}
}

void Game::Update()
{
}

void Game::Render(float interpolation)
{
}

