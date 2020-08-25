#include"Button.h"
#include"Font.h"
#include"ScreenText.h"
#include"Texture.h"
#include "UIScreen.h"
#include"Game.h"
#include"StartMenuScreen.h"
#include"Othello.h"

StartMenuScreen::StartMenuScreen(){
}

StartMenuScreen::~StartMenuScreen(){
}

void StartMenuScreen::Init(class Game* game) {
	
	mGame = game;
	mInputSystem = &(game->mInputSystem);
	
	// フォント初期化
	FontInit();

	// 背景初期化
	TextureInit();

	// ボタン初期化
	ButtonInit();

	// テキスト初期化
	ScreenTextInit();
}

void StartMenuScreen::FontInit() {
	mFont = mGame->AddFont("default");
}

void StartMenuScreen::ButtonInit() {

	// 開始ボタン
	AddButton(
		"Game Start",
		[this]() {
			if (mStartMenuMode == StartMenuScreen::eStartMenu) { // スタート時のみ有効
				mStartMenuMode = StartMenuScreen::eFirstPlayerSelect;
				GetButton("Game Start")->Activate(false);
				GetButton("Firstmove")->Activate(true);
				GetButton("Passivemove")->Activate(true);
			}
		},
		{300,200}, {100,100}, // サイズ未定義
		mGame->GetTexture("NormalButton"), mGame->GetTexture("NormalButton"),
		true
	);

	// 黒（先手）選択
	AddButton(
		"Firstmove", 
		[this]() {
			if (mStartMenuMode == StartMenuScreen::eFirstPlayerSelect) {
				mGame->mOthello.BoardInit(Othello::eBlack);
				mGame->SetGameMode(Game::ePlaying);
				GetButton("Game Start")->Activate(true);
				GetButton("Firstmove")->Activate(false);
				GetButton("Passivemove")->Activate(false);
				mStartMenuMode = StartMenuScreen::eStartMenu; // test
			}
		},
		{300,100}, {80,40},	// サイズ未定義
		mGame->GetTexture("NormalButton"), mGame->GetTexture("NormalButton"),
		false
	);

	// 白（後手）選択
	AddButton(
		"Passivemove",
		[this]() {
			if (mStartMenuMode == StartMenuScreen::eFirstPlayerSelect) {
				mGame->mOthello.BoardInit(Othello::eWhite);
				mGame->SetGameMode(Game::ePlaying);
				GetButton("Game Start")->Activate(true);
				GetButton("Firstmove")->Activate(false);
				GetButton("Passivemove")->Activate(false);
				mStartMenuMode = StartMenuScreen::eStartMenu; // test
			}
		},	// サイズ未定義
		{400,200}, {80,40},
		mGame->GetTexture("NormalButton"), mGame->GetTexture("HighlightedButton"),
		false
	);

	AddButton(
		"Exit",
		[this]() {
			mGame->QuitGame();
		},
		{ 540, 450 }, { 240, 40 }
		,
		mGame->GetTexture("NormalButton"), mGame->GetTexture("HighlightedButton"),
		true
	);
}

void StartMenuScreen::ScreenTextInit() {
	
	// タイトルテキスト（未定）

	// モード選択テキスト（未実装）

	// 手番選択テキスト

}

void StartMenuScreen::TextureInit() {
	// 背景画像
	mBGTexture = mGame->GetTexture("StartMenuBG");

}