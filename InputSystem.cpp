#include "InputSystem.h"
#include "Game.h"

InputSystem::InputSystem(){
	mMouseState = MouseState();
}

void InputSystem::Init(class Game* game) {
	mGame = game;
}

void InputSystem::Polling() {

	// �e���͂Ń|�[�����O�����ď�Ԃ�����
	mMouseState.Polling();

}