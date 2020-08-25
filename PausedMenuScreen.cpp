#include"Button.h"
#include"Font.h"
#include"ScreenText.h"
#include"Texture.h"
#include "UIScreen.h"
#include "Game.h"
#include"PausedMenuScreen.h"

void PausedMenuScreen::Init(Game* game) {
	mGame = game;
	mInputSystem = &(game->mInputSystem);

	FontInit();

	ScreenTextInit();

	ButtonInit();

	TextureInit();

}

void PausedMenuScreen::FontInit() {
	mFont = mGame->AddFont("default");
}

void PausedMenuScreen::ScreenTextInit() {
}

void PausedMenuScreen::ButtonInit() {
	AddButton(
		"Resume",
		[this]() {
			mGame->SetGameMode(Game::ePlaying);
		},
		{ 540, 450 }, { 240, 40 },
		mGame->GetTexture("NormalButton"), mGame->GetTexture("HighlightedButton"),
		true
	);

	AddButton(
		"Exit",
		[this]() {
			mGame->QuitGame();
		},
		{ 540, 500 }, { 240, 40 }
		,
		mGame->GetTexture("NormalButton"), mGame->GetTexture("HighlightedButton"),
		true
	);
}

void PausedMenuScreen::TextureInit() {
	// ”wŒi‰æ‘œ
	mBGTexture = mGame->GetTexture("PauseMenuBG");
}