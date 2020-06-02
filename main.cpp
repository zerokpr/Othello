#include"DxLib.h"
#include"Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game;

	if (!(game.Initialize())) {
		return 0;
	}
	// printfDx("初期化成功\n");
	game.MainLoop();
	printfDx("メインループ完了\n");
	game.Shutdown();

	return 0;
}

