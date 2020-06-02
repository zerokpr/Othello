#include"DxLib.h"
#include"Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game;

	if (!(game.Initialize())) {
		return 0;
	}
	// printfDx("‰Šú‰»¬Œ÷\n");
	game.MainLoop();
	printfDx("ƒƒCƒ“ƒ‹[ƒvŠ®—¹\n");
	game.Shutdown();

	return 0;
}

