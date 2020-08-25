#include "Othello.h"
#include "OthelloAI.h"
#include "Vector.h"

void OthelloAI::Init(Othello* othello, int AIcolor) {
	mOthello = othello;
	mColor = AIcolor;
}

// テスト未実施
Vector2 OthelloAI::OutPut(int board[8][8]) {
	int y= -1, x = -1, vmax = -1;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int tmpval = Value(j, i, board);
			if (vmax < tmpval) {
				vmax = tmpval;
				y = i;
				x = j;
			}
		}
	}
	return Vector2(static_cast<double>(x), static_cast<double>(y));
}

// テスト未実施
int OthelloAI::Value(int x, int y, int board[8][8]) {
	if (!mOthello->Play(x, y, mColor, true)) return -1;
	int ret = 0;
	if (2 <= x && x <= 5 && 2 <= y && y <= 5) ret += 2;
	if (
		(2 <= x && x <= 5 && (y == 1 || y == 6)) ||
		(2 <= y && y <= 5 && (x == 1 || x == 6))
	) ret += 1;
	if (
		(2 <= x && x <= 5 && (y == 0 || y == 7)) ||
		(2 <= y && y <= 5 && (x == 0 || x == 7))
	) ret += 4;
	if (((x == 0 || x == 7) && (y == 0 || y == 7))) ret += 100;

	return ret;
}