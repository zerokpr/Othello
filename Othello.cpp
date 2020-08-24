#include"Game.h"
#include "Othello.h"
#include"Texture.h"

void Othello::Init(Game* game){

	mGame = game;
	mInputSystem = &(game->mInputSystem);

	FlagInit();

	LoadData(); // �摜��Game�N���X�֓ǂݍ���

	TextureInit();  // �摜������
	
	ScreenTextInit(); // �\���e�L�X�g�ȂǏ�����
	
	DimensionInit(mGame->mScreenSizeX*0.05, mGame->mScreenSizeX*0.05, 420, 420); // ���@������

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
	// �w�i�摜
	BGTex = mGame->GetTexture("OthelloBG");

	// ��
	BlackTex = mGame->GetTexture("BlackPiece");

	// ��
	WhiteTex = mGame->GetTexture("WhitePiece");

}

void Othello::ScreenTextInit() {
	// �Ֆʂ̏󋵕\���i�R�}���j
	
	// ��ԕ\��

}

void Othello::DimensionInit(int posx, int posy, int sizex, int sizey) {
	mPos = Vector2(posx, posy);
	mSize = Vector2(sizex, sizey);
}

// �e�X�g�����{
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

// �e�X�g�ς�
bool Othello::ContainsPoint(const Vector2& pt) {
	return (
		pt.x >= mPos.x &&
		pt.x < (mPos.x + mSize.x) &&
		pt.y >= mPos.y &&
		pt.y < (mPos.y + mSize.y)
	);
}

// �e�X�g�����{
void Othello::CalcPoint(const Vector2 &pt) {
	mPlayPointX = int(pt.x - mPos.x) / int(mSize.x/8.0);
	mPlayPointY = int(pt.y - mPos.y) / int(mSize.y/8.0);
}

// �e�X�g�����{
void Othello::ProcessInput() {
	
	// �N���b�N����
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

	// �v���C���[�̃^�[��
	if (mNowPlayer == ePlayer) {
		if (needPass(mBoard, mNowPlayer)) {
			ChangeTurn();
		} else {
			if (mIsClicked) { // �N���b�N���������ꍇ
				if (Play(mPlayPointX, mPlayPointY, mPlayerColor, true)) {
					Play(mPlayPointX, mPlayPointY, mPlayerColor, false);
					mPlayPointX = -1; mPlayPointY = -1;
					ChangeTurn();
				}
			}
		}
	}
	
	// AI�̃^�[��
	if (mNowPlayer == eAI) {
		Vector2 tmp = mOthelloAI.OutPut(mBoard);
		mPlayPointX = tmp.x; mPlayPointY = tmp.y;
		Play(mPlayPointX, mPlayPointY, mAIColor, false); // AI���p�X�������炱���Ō��m����悤�ɂ��Ă��悢.
		ChangeTurn();
	}

	// ������X�V�iTODO�j

	mIsClicked = false;
}

void Othello::Draw() {

	// �`��
	DrawTexture();
	
	// �e�L�X�g�`��
	DrawScreenText();
	
}

// �e�X�g�����{
void Othello::DrawTexture() {
	// �w�i
	BGTex->Draw(mPos.x, mPos.y, mSize.x, mSize.y);
	
	// ��
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (mBoard[i][j] == eBlack) { // ��
				BlackTex->Draw(mPos.x + (mSize.x/8)*j, mPos.y + (mSize.y/8)*i, mSize.x/8, mSize.y/8);
			}
			else if(mBoard[i][j] == eWhite){ // ��
				WhiteTex->Draw(mPos.x + (mSize.x/8)*j, mPos.y + (mSize.y/8)*i, mSize.x/8, mSize.y/8);
			}
		}
	}
}

void Othello::DrawScreenText() {

}

// �e�X�g�ς�
int Othello::Play(int x, int y, int player, bool isThink) {
	if (x < 0 || y < 0) return 0;
	if (mBoard[y][x] != -1) return 0;
	int cnt = 0; // �Ђ�����Ԃ���̐�
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			if (i == 0 && j == 0) continue; // ���O
			
			int tmpcnt = 0;
			int ny = y, nx = x;
			for (int k = 0; k <= 7; ++k) {
				ny += i; nx += j;
				if (ny < 0 || ny >= 8 || nx < 0 || nx >= 8 || mBoard[ny][nx] == -1) { // �͈͊O���A�����Ȃ��}�X
					tmpcnt = 0;
					break;
				}
				if (mBoard[ny][nx] == (player ^ 1)) ++tmpcnt; // �v���C���[�̋�ƈႤ�F�̋�̏ꍇ
				if (mBoard[ny][nx] == player) break; // �����Ȃ�I��
			}
			ny = y; nx = x;
			if (tmpcnt > 0 && !isThink) { // �Ђ�����Ԃ���ꍇ�A�ՖʍX�V
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