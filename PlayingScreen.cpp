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
			mGame->SetGameMode(Game::ePaused);
		},
		{ 540, 450 }, { 240, 40 },
		mGame->GetTexture("NormalButton"), mGame->GetTexture("HighlightedButton"),
		true
	);
}

void PlayingScreen::TextureInit() {
	// ”wŒi‰æ‘œ 
	mBGTexture = mGame->GetTexture("PlayingBG");
}