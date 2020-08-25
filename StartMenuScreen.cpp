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
	
	// �t�H���g������
	FontInit();

	// �w�i������
	TextureInit();

	// �{�^��������
	ButtonInit();

	// �e�L�X�g������
	ScreenTextInit();
}

void StartMenuScreen::FontInit() {
	mFont = mGame->AddFont("default");
}

void StartMenuScreen::ButtonInit() {

	// �J�n�{�^��
	AddButton(
		"Game Start",
		[this]() {
			if (mStartMenuMode == StartMenuScreen::eStartMenu) { // �X�^�[�g���̂ݗL��
				mStartMenuMode = StartMenuScreen::eFirstPlayerSelect;
				GetButton("Game Start")->Activate(false);
				GetButton("Firstmove")->Activate(true);
				GetButton("Passivemove")->Activate(true);
			}
		},
		{300,200}, {100,100}, // �T�C�Y����`
		mGame->GetTexture("NormalButton"), mGame->GetTexture("NormalButton"),
		true
	);

	// ���i���j�I��
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
		{300,100}, {80,40},	// �T�C�Y����`
		mGame->GetTexture("NormalButton"), mGame->GetTexture("NormalButton"),
		false
	);

	// ���i���j�I��
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
		},	// �T�C�Y����`
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
	
	// �^�C�g���e�L�X�g�i����j

	// ���[�h�I���e�L�X�g�i�������j

	// ��ԑI���e�L�X�g

}

void StartMenuScreen::TextureInit() {
	// �w�i�摜
	mBGTexture = mGame->GetTexture("StartMenuBG");

}