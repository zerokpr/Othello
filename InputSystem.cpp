#include "InputSystem.h"
#include "Game.h"

InputSystem::InputSystem(){
	mMouseState = MouseState();
}

void InputSystem::Init(class Game* game) {
	mGame = game;
}

void InputSystem::Polling() {

	// 各入力でポーリングをして状態を見る
	mMouseState.Polling();

}