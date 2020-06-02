#pragma once
#include "Vector.h"

class Game;
class Texture;
class Othello
{
public:
	//Othello(class Game* game, class InputSystem* inputsystem){}

	enum PieceColor{
		eBlack, // 先行
		eWhite  // 後攻
	};

	enum Player{
		ePlayer,
		eAI
	};

	void Init(); // 画像など全体初期化, Game全体の初期化で呼ばれる
	void TextureInit();    // 画像初期化
	void ScreenTextInit(); // 表示

	// 盤面初期化
	// playerColor：Black:プレイヤー先行, White:AI先行
	// StartMenuScreenで呼ばれる
	void BoardInit(enum PieceColor playerColor);
	void ProcessInput();	// 入力処理 ポーリングの後に呼ばれる
	void Update();			// ゲーム更新 未実装
	void Draw();			// 
	void DrawTexture();		// 画像描画
	void DrawScreenText();  // 文字列描画

private:
	// [y][x]
	int mBoard[8][8]; // 盤面状態 0:駒なし 1,2:各プレイヤーの駒がある
	enum Player mNowPlayer; // 現在の手番(1: プレイヤー, 2: CP)
	enum PieceColor mPlayerColor; // プレイヤーの色
	
	bool Play(int y, int x, bool isThink) { return true; } // 手を打つ
	bool CheckGameEnd() { return true; } // ゲームが終わったかをチェック

	bool mIsClicked;

	Texture* BGTex;
	Texture* BlackTex;
	Texture* WhiteTex;

	Vector2 mPos;
	Vector2 mSize;

	Game* mGame; // ゲームへの参照
};
