#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#include "Game.h"

int main()
{
	Game game;
	return game.Run();
}