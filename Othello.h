#pragma once
#include "Vector.h"

class Game;
class Texture;
class Othello
{
public:
	//Othello(class Game* game, class InputSystem* inputsystem){}

	enum PieceColor{
		eBlack, // ��s
		eWhite  // ��U
	};

	enum Player{
		ePlayer,
		eAI
	};

	void Init(); // �摜�ȂǑS�̏�����, Game�S�̂̏������ŌĂ΂��
	void TextureInit();    // �摜������
	void ScreenTextInit(); // �\��

	// �Ֆʏ�����
	// playerColor�FBlack:�v���C���[��s, White:AI��s
	// StartMenuScreen�ŌĂ΂��
	void BoardInit(enum PieceColor playerColor);
	void ProcessInput();	// ���͏��� �|�[�����O�̌�ɌĂ΂��
	void Update();			// �Q�[���X�V ������
	void Draw();			// 
	void DrawTexture();		// �摜�`��
	void DrawScreenText();  // ������`��

private:
	// [y][x]
	int mBoard[8][8]; // �Ֆʏ�� 0:��Ȃ� 1,2:�e�v���C���[�̋����
	enum Player mNowPlayer; // ���݂̎��(1: �v���C���[, 2: CP)
	enum PieceColor mPlayerColor; // �v���C���[�̐F
	
	bool Play(int y, int x, bool isThink) { return true; } // ���ł�
	bool CheckGameEnd() { return true; } // �Q�[�����I����������`�F�b�N

	bool mIsClicked;

	Texture* BGTex;
	Texture* BlackTex;
	Texture* WhiteTex;

	Vector2 mPos;
	Vector2 mSize;

	Game* mGame; // �Q�[���ւ̎Q��
};
