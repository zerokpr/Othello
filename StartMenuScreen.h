#pragma once
#include "UIScreen.h"

class StartMenuScreen : public UIScreen
{
public:
	StartMenuScreen();
	~StartMenuScreen();

	virtual void Init(class Game* game);
	virtual void FontInit(); // フォント指定
	virtual void ScreenTextInit();
	virtual void ButtonInit();
	virtual void TextureInit();
	// virtual void ProcessInput();
	// virtual void Update();
	// virtual void Draw();

private:

	// ボタンでゲームモードを決める
	enum StartMenuState {	// 
		eStartMenu,			// スタート画面
		eModeSelect,		// モード選択（未実装、オセロ以外も選択できるようにするならアリかも）
		eFirstPlayerSelect,	// 手番選択画面
		eExit				// ゲーム退出選択画面
	} mStartMenuMode;
};