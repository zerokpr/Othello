#pragma once
#include"MouseState.h"

class Game;
class InputSystem
{
public:

	InputSystem();
	~InputSystem() {}

	void Init(class Game* game);

	// �}�E�X��ԕۑ�
	MouseState mMouseState;

	// �e���͂��󂯕t����
	void Polling();

private:

	// Game�ւ̎Q��
	class Game* mGame;
};