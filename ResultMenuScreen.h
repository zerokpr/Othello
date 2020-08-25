#pragma once
#include"UIScreen.h"

class ResultMenuScreen : public UIScreen
{
public:
	virtual void Init(class Game* game);
	virtual void FontInit(); // フォント指定
	virtual void ScreenTextInit();
	virtual void ButtonInit();
	virtual void TextureInit();
	// virtual void ProcessInput();
	// virtual void Update();
	// virtual void Draw();

	void ResultInput(int blackpoint, int whitepoint);

private:
	int mBlackPoint, mWhitePoint;
};