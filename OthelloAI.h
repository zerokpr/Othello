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
	int mColor; // AI�̋�̐F
	Vector2 OutPut(int board[8][8]); // ��̏o��
	int Value(int x, int y, int board[8][8]); // �]���֐�

};

