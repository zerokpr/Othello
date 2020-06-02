#pragma once
#include"MouseState.h"

class Game;
class InputSystem
{
public:

	InputSystem();
	~InputSystem() {}

	void Init(class Game* game);

	// マウス状態保存
	MouseState mMouseState;

	// 各入力を受け付ける
	void Polling();

private:

	// Gameへの参照
	class Game* mGame;
};