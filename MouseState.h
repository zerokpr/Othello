#pragma once
#include"Vector.h"

class MouseState
{
public:
	MouseState();
	//~MouseState();
	bool wasClicked(void);
	void ClickEventEnd(void);
	void Polling(); // �|�[�����O
	Vector2 MousePos(void);

private:
	bool mPrevOnPressed, mCurrOnPressed;
	int mPrevMouseX, mPrevMouseY;
	int mCurrMouseX, mCurrMouseY;
	bool mWasClicked; // �N���b�N�C�x���g�����������ǂ���
};