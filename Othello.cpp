#include"Game.h"
#include "Othello.h"
#include"Texture.h"

void Othello::Init(Game* game){

	mGame = game;
	mInputSystem = &(game->mInputSystem);

	FlagInit();

	LoadData(); // 画像をGameクラスへ読み込む

	TextureInit();  // 画像初期化
	
	ScreenTextInit(); // 表示テキストなど初期化
	
	DimensionInit(mGame->mScreenSizeX*0.05, mGame->mScreenSizeX*0.05, 420, 420); // 寸法初期化

}

void Othello::FlagInit() {
	mIsClicked = false;
	mIsClicked = false;
}

void Othello::LoadData() {
	mGame->AddTexture("OthelloBG", "OthelloBG.jpg");
	mGame->AddTexture("BlackPiece", "BlackPiece.jpg");
	mGame->AddTexture("WhitePiece", "WhitePiece.jpg");
}

void Othello::TextureInit() {
	// 背景画像
	BGTex = mGame->GetTexture("OthelloBG");

	// 黒
	BlackTex = mGame->GetTexture("BlackPiece");

	// 白
	WhiteTex = mGame->GetTexture("WhitePiece");

}

void Othello::ScreenTextInit() {
	// 盤面の状況表示（コマ数）
	
	// 手番表示

}

void Othello::DimensionInit(int posx, int posy, int sizex, int sizey) {
	mPos = Vector2(posx, posy);
	mSize = Vector2(sizex, sizey);
}

// テスト未実施
void Othello::BoardInit(enum Othello::PieceColor playerColor) {
	mPlayerColor = playerColor;
	
	if (mPlayerColor == eBlack) {
		mNowPlayer = ePlayer;
		mAIColor = eWhite;
	} else {
		mNowPlayer = eAI;
		mAIColor = eBlack;
	}
	
	mOthelloAI.Init(this, mAIColor);
	
	for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) mBoard[i][j] = eNone;
	for (int i = 3; i <= 4; ++i) {
		mBoard[i][i] = eBlack;
		mBoard[i][7 - i] = eWhite;
	}
}

// テスト済み
bool Othello::ContainsPoint(const Vector2& pt) {
	return (
		pt.x >= mPos.x &&
		pt.x < (mPos.x + mSize.x) &&
		pt.y >= mPos.y &&
		pt.y < (mPos.y + mSize.y)
	);
}

// テスト未実施
void Othello::CalcPoint(const Vector2 &pt) {
	mPlayPointX = int(pt.x - mPos.x) / int(mSize.x/8.0);
	mPlayPointY = int(pt.y - mPos.y) / int(mSize.y/8.0);
}

// テスト未実施
void Othello::ProcessInput() {
	
	// クリック処理
	if (ContainsPoint(mInputSystem->mMouseState.MousePos())) {
		if (mInputSystem->mMouseState.wasClicked()) {
			if (mNowPlayer == ePlayer) {
				CalcPoint(mInputSystem->mMouseState.MousePos());
				mIsClicked = true;
			}
			mInputSystem->mMouseState.ClickEventEnd();
		}
	}
}

void Othello::ChangeTurn() {
	if (mNowPlayer == ePlayer) {
		mNowPlayer = eAI;
	} else {
		mNowPlayer = ePlayer;
	}
}

bool Othello::needPass(int board[8][8], int player) {
	return false;
}

void Othello::Update() {

	// プレイヤーのターン
	if (mNowPlayer == ePlayer) {
		if (needPass(mBoard, mNowPlayer)) {
			ChangeTurn();
		} else {
			if (mIsClicked) { // クリックがあった場合
				if (Play(mPlayPointX, mPlayPointY, mPlayerColor, true)) {
					Play(mPlayPointX, mPlayPointY, mPlayerColor, false);
					mPlayPointX = -1; mPlayPointY = -1;
					ChangeTurn();
				}
			}
		}
	}
	
	// AIのターン
	if (mNowPlayer == eAI) {
		Vector2 tmp = mOthelloAI.OutPut(mBoard);
		mPlayPointX = tmp.x; mPlayPointY = tmp.y;
		Play(mPlayPointX, mPlayPointY, mAIColor, false); // AIがパスだったらここで検知するようにしてもよい.
		ChangeTurn();
	}

	// 文字列更新（TODO）

	mIsClicked = false;
}

void Othello::Draw() {

	// 描画
	DrawTexture();
	
	// テキスト描画
	DrawScreenText();
	
}

// テスト未実施
void Othello::DrawTexture() {
	// 背景
	BGTex->Draw(mPos.x, mPos.y, mSize.x, mSize.y);
	
	// 駒
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (mBoard[i][j] == eBlack) { // 黒
				BlackTex->Draw(mPos.x + (mSize.x/8)*j, mPos.y + (mSize.y/8)*i, mSize.x/8, mSize.y/8);
			}
			else if(mBoard[i][j] == eWhite){ // 白
				WhiteTex->Draw(mPos.x + (mSize.x/8)*j, mPos.y + (mSize.y/8)*i, mSize.x/8, mSize.y/8);
			}
		}
	}
}

void Othello::DrawScreenText() {

}

// テスト済み
int Othello::Play(int x, int y, int player, bool isThink) {
	if (x < 0 || y < 0) return 0;
	if (mBoard[y][x] != -1) return 0;
	int cnt = 0; // ひっくり返す駒の数
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			if (i == 0 && j == 0) continue; // 除外
			
			int tmpcnt = 0;
			int ny = y, nx = x;
			for (int k = 0; k <= 7; ++k) {
				ny += i; nx += j;
				if (ny < 0 || ny >= 8 || nx < 0 || nx >= 8 || mBoard[ny][nx] == -1) { // 範囲外か、何もないマス
					tmpcnt = 0;
					break;
				}
				if (mBoard[ny][nx] == (player ^ 1)) ++tmpcnt; // プレイヤーの駒と違う色の駒の場合
				if (mBoard[ny][nx] == player) break; // 同じなら終了
			}
			ny = y; nx = x;
			if (tmpcnt > 0 && !isThink) { // ひっくり返せる場合、盤面更新
				for (int k = 0; k <= 7; ++k) {
					ny += i; nx += j;
					if (mBoard[ny][nx] == player) break;
					mBoard[ny][nx] ^= 1;
				}
			}
			cnt += tmpcnt;
		}
	}

	if (cnt > 0 && !isThink) mBoard[y][x] = player;

	return cnt;
}