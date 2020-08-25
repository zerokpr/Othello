#include"Button.h"
#include"Font.h"
#include"ScreenText.h"
#include"Texture.h"
#include "UIScreen.h"
#include "Game.h"
#include "ResultMenuScreen.h"


void ResultMenuScreen::Init(Game* game) {
	mGame = game;
	mInputSystem = &(game->mInputSystem);

	FontInit();

	ScreenTextInit();

	ButtonInit();

	TextureInit();

}

void ResultMenuScreen::FontInit() {
	mFont = mGame->AddFont("default");
}

void ResultMenuScreen::ScreenTextInit() {

	/* Œ‹‰Ê•\Ž¦ */
	// •”’•\Ž¦
	AddScreenText(
		"BlackWhite",
		"Black : White",
		{50, 50},
		50,
		{256, 256, 256}
	);
	// Œ‹‰Ê”’l
	AddScreenText(
		"Result",
		"test",
		{ 50, 150 },
		50,
		{ 256, 256, 256 }
	);
	
}

void ResultMenuScreen::ButtonInit() {
	AddButton(
		"BackToStartMenu",
		[this]() {
			mGame->SetGameMode(Game::eStartMenu);
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

void ResultMenuScreen::TextureInit() {
	mBGTexture = mGame->GetTexture("ResultMenuBG");
}

void ResultMenuScreen::ResultInput(int blackpoint, int whitepoint) {
	mBlackPoint = blackpoint;
	mWhitePoint = whitepoint;
	GetScreenText("Result")->ChangeText(std::to_string(mBlackPoint) + " " + std::to_string(mWhitePoint));
}