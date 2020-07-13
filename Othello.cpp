#include"Game.h"
#include "Othello.h"
#include"Texture.h"


void Othello::Init(Game* game){
	mGame = game;

	mIsClicked = false; // �t���O������

	TextureInit();  // �摜������
	
	ScreenTextInit(); // �\���e�L�X�g�ȂǏ�����
	
}

void Othello::TextureInit() {
	// �w�i�摜
	BGTex = mGame->GetTexture("OthelloBG.jpg");

	// ��
	BlackTex = mGame->GetTexture("OthelloBlack.jpg");

	// ��
	WhiteTex = mGame->GetTexture("OthelloWhite.jpg");

}

void Othello::ScreenTextInit() {
	// �Ֆʂ̏󋵕\���i�R�}���j
	
	// ��ԕ\��

}

void Othello::BoardInit(enum Othello::PieceColor playerColor) {
	mPlayerColor = playerColor;
	if (mPlayerColor == eBlack) mNowPlayer = ePlayer;
	else mNowPlayer = eAI;
	for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) mBoard[i][j] = 0;
	for (int i = 3; i <= 4; ++i) for (int j = 3; j <= 4; ++j) {
		mBoard[i][j] = 1;
		mBoard[i][7 - j] = 2;
	}
}

void Othello::ProcessInput() {
	
	// �N���b�N����

}

void Othello::Update() {

	// �N���b�N���������ꍇ�A�����ɑł��Ƃ��\���𔻒�

	// �N���b�N�t���O��؂�

	// ������X�V

}

void Othello::Draw() {

	// �`��
	DrawTexture();
	
	// �e�L�X�g�`��
	DrawScreenText();
	
}

void Othello::DrawTexture() {
	// �w�i
	BGTex->Draw(mPos.x, mPos.y, mSize.x, mSize.y);
	
	// ��
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (mBoard[i][j] == 1) { // ��
				BlackTex->Draw(mPos.x + (mSize.x/8)*j, mPos.y + (mSize.y/8)*i, mSize.x/8, mSize.y/8);
			}
			else if(mBoard[i][j] == 2){ // ��
				WhiteTex->Draw(mPos.x + (mSize.x / 8) * j, mPos.y + (mSize.y / 8) * i, mSize.x / 8, mSize.y / 8);
			}
		}
	}
}

void Othello::DrawScreenText() {

}