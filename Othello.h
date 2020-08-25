#pragma once
#include "Vector.h"
#include "OthelloAI.h"

class Game;
class InputSystem;
class Texture;
class Othello
{
	friend OthelloAI;
public:

	Othello():mPos(0,0), mSize(0,0){}
	enum PieceColor{
		eNone = -1, // 何もない状態
		eBlack = 0, // 先行
		eWhite = 1// 後攻
	};

	enum Player{
		ePlayer,
		eAI
	};

	void Init(Game* game); // 画像など全体初期化, Game全体の初期化で呼ばれる
	void FlagInit();		// 各種フラグ初期化
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
	void Update();			// ゲーム更新

	void Draw();			// 描画
	void DrawTexture();		// 画像描画
	void DrawScreenText();  // 文字列描画
	int mBlackPoint, mWhitePoint;

	bool CheckGameEnd(); // ゲームが終わったかをチェック

private:
	// [y][x]
	int mBoard[8][8]; // 盤面状態 -1:駒なし 0,1:各プレイヤーの駒がある.
	enum Player mNowPlayer; // 現在の手番
	enum PieceColor mPlayerColor; // プレイヤーの色
	enum PieceColor mAIColor; // AIの色

	int mPassCount; // 連続するパスの回数
	
	int mPlayPointX, mPlayPointY; // 打たれた手の位置
	void CalcPoint(const Vector2 &pt); // クリック位置をマスの座標に変換
	
	void ChangePieceNum(int color, int point);
	void ChangeTurn(); // ターン交代
	bool ContainsPoint(const Vector2 &pt); // ptが座標がボードに含まれるか
	bool mIsClicked; // ボードがクリックされたか
	int Play(int x, int y, int player, bool isThink); // 手を打つ
	bool CheckPass(int board[8][8], int player);

	// AI
	OthelloAI mOthelloAI;

	// 画像
	Texture* BGTex;
	Texture* BlackTex;
	Texture* WhiteTex;

	// 表示文字

	// 位置, サイズ
	Vector2 mPos;
	Vector2 mSize;

	Game* mGame; // ゲームへの参照
	InputSystem* mInputSystem;
};
