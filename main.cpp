#include"DxLib.h"
#include"Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game;

	if (!(game.Initialize())) {
		return 0;
	}
	// printfDx("����������\n");
	game.MainLoop();
	printfDx("���C�����[�v����\n");
	game.Shutdown();

	return 0;
}

