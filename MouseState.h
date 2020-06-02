#pragma once
#include"Vector.h"

class MouseState
{
public:
	MouseState();
	//~MouseState();
	bool wasClicked(void);
	void ClickEventEnd(void);
	void Polling(); // ポーリング
	Vector2 MousePos(void);

private:
	bool mPrevOnPressed, mCurrOnPressed;
	int mPrevMouseX, mPrevMouseY;
	int mCurrMouseX, mCurrMouseY;
	bool mWasClicked; // クリックイベントが未処理かどうか
};