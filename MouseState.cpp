#include "MouseState.h"
#include"DxLib.h"

MouseState::MouseState() {
	mWasClicked = false;
	mPrevOnPressed = mCurrOnPressed = false;
	mPrevMouseX = mPrevMouseY = 0;
	mCurrMouseX = mCurrMouseY = 0;
}

void MouseState::Polling() {

	// ���ݏ�ԍX�V
	mCurrOnPressed = GetMouseInput() & MOUSE_INPUT_LEFT;
	GetMousePoint(&mCurrMouseX, &mCurrMouseY);

	// �N���b�N�C�x���g�Ď�
	if (mPrevOnPressed && !mCurrOnPressed) {
		mWasClicked = true;
	}
	if (!mPrevOnPressed && !mCurrOnPressed) {
		mWasClicked = false;
	}

	// �O�t���[����ԍX�V
	mPrevOnPressed = mCurrOnPressed;
	mPrevMouseX = mCurrMouseX;
	mPrevMouseY = mCurrMouseY;
}

bool MouseState::wasClicked(void) {
	return mWasClicked;
}

void MouseState::ClickEventEnd(void) {
	mWasClicked = false;
}


Vector2 MouseState::MousePos(){
	return Vector2(static_cast<double>(mCurrMouseX), static_cast<double>(mCurrMouseY));
}
