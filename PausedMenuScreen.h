#pragma once
#include "UIScreen.h"

class PausedMenuScreen : public UIScreen
{
public:
	PausedMenuScreen(){}
	~PausedMenuScreen(){}

	virtual void Init(class Game* game);
	virtual void FontInit(); // �t�H���g�w��
	virtual void ScreenTextInit();
	virtual void ButtonInit();
	virtual void TextureInit();
	// virtual void ProcessInput();
	// virtual void Update();
	// virtual void Draw();
};

