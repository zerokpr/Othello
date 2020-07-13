#include"Game.h"
#include"InputSystem.h"
#include"Othello.h"
#include"OthelloAI.h"
#include"UIScreen.h"
#include "PlayingScreen.h"

void PlayingScreen::Init(class Game* game) {

	mGame = game;
	mInputSystem = &(game->mInputSystem);

	FontInit();

	ScreenTextInit();

	ButtonInit();

	TextureInit();
}

void PlayingScreen::FontInit() {
	mFont = mGame->AddFont("default");
}

void PlayingScreen::ScreenTextInit() {
}

void PlayingScreen::ButtonInit() {
	AddButton(
		"Pause",
		[this]() {
			mGame->SetGameMode(Game::eStartMenu); // テスト中の為スタート画面に戻る
		},
		{500,400}, {100,30},
		mGame->GetTexture("NormalButton"), mGame->GetTexture("HighlightedButton"),
		true
	);
}

void PlayingScreen::TextureInit() {
	// 背景画像 
	mBGTexture = mGame->GetTexture("PlayingBG");
}