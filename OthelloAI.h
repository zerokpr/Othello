#pragma once
#include"Vector.h"

class Othello;
class OthelloAI
{
public:
	OthelloAI(){}
	~OthelloAI(){}

	void Init(Othello* othello, int AIcolor);
	
	Othello* mOthello;
	int mColor; // AIの駒の色
	Vector2 OutPut(int board[8][8]); // 手の出力
	int Value(int x, int y, int board[8][8]); // 評価関数

};

