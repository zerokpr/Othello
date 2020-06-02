#pragma once
#include"UIScreen.h"

// プレイ画面の内、オセロ盤以外の機能
// 
class PlayingScreen : public UIScreen
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

private:

};