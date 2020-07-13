#include"Game.h"
#include "Othello.h"
#include"Texture.h"


void Othello::Init(Game* game){
	mGame = game;

	mIsClicked = false; // フラグ初期化

	TextureInit();  // 画像初期化
	
	ScreenTextInit(); // 表示テキストなど初期化
	
}

void Othello::TextureInit() {
	// 背景画像
	BGTex = mGame->GetTexture("OthelloBG.jpg");

	// 黒
	BlackTex = mGame->GetTexture("OthelloBlack.jpg");

	// 白
	WhiteTex = mGame->GetTexture("OthelloWhite.jpg");

}

void Othello::ScreenTextInit() {
	// 盤面の状況表示（コマ数）
	
	// 手番表示

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
	
	// クリック処理

}

void Othello::Update() {

	// クリックがあった場合、そこに打つことが可能かを判定

	// クリックフラグを切る

	// 文字列更新

}

void Othello::Draw() {

	// 描画
	DrawTexture();
	
	// テキスト描画
	DrawScreenText();
	
}

void Othello::DrawTexture() {
	// 背景
	BGTex->Draw(mPos.x, mPos.y, mSize.x, mSize.y);
	
	// 駒
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (mBoard[i][j] == 1) { // 黒
				BlackTex->Draw(mPos.x + (mSize.x/8)*j, mPos.y + (mSize.y/8)*i, mSize.x/8, mSize.y/8);
			}
			else if(mBoard[i][j] == 2){ // 白
				WhiteTex->Draw(mPos.x + (mSize.x / 8) * j, mPos.y + (mSize.y / 8) * i, mSize.x / 8, mSize.y / 8);
			}
		}
	}
}

void Othello::DrawScreenText() {

}