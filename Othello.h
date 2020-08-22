#pragma once
#include "Vector.h"

class Game;
class InputSytem;
class Texture;
class Othello
{
public:

	Othello():mPos(0,0), mSize(0,0){}
	enum PieceColor{
		eBlack, // 先行
		eWhite  // 後攻
	};

	enum Player{
		ePlayer,
		eAI
	};

	void Init(Game* game); // 画像など全体初期化, Game全体の初期化で呼ばれる
	void TextureInit();    // 画像初期化
	void ScreenTextInit(); // 表示

	void LoadData();

	// ゲーム盤寸法初期化
	void DimensionInit(int posx, int posy, int sizex, int sizey);

	// 盤面初期化
	// playerColor：Black:プレイヤー先行, White:AI先行
	// StartMenuScreenで呼ばれる
	void BoardInit(enum PieceColor playerColor);

	void ProcessInput();	// 入力処理 ポーリングの後に呼ばれる
	void Update();			// ゲーム更新 未実装

	void Draw();			// 描画
	void DrawTexture();		// 画像描画
	void DrawScreenText();  // 文字列描画

private:
	// [y][x]
	int mBoard[8][8]; // 盤面状態 0:駒なし 1,2:各プレイヤーの駒がある
	enum Player mNowPlayer; // 現在の手番(1: プレイヤー, 2: CP)
	enum PieceColor mPlayerColor; // プレイヤーの色
	
	bool Play(int y, int x, bool isThink) { return true; } // 手を打つ
	bool CheckGameEnd() { return true; } // ゲームが終わったかをチェック

	bool mIsClicked; // ボードがクリックされたか

	// 画像
	Texture* BGTex;
	Texture* BlackTex;
	Texture* WhiteTex;

	// 位置, サイズ
	Vector2 mPos;
	Vector2 mSize;

	Game* mGame; // ゲームへの参照
	InputSystem* mInputSystem;
};
