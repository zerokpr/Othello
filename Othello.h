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
		eBlack, // ��s
		eWhite  // ��U
	};

	enum Player{
		ePlayer,
		eAI
	};

	void Init(Game* game); // �摜�ȂǑS�̏�����, Game�S�̂̏������ŌĂ΂��
	void TextureInit();    // �摜������
	void ScreenTextInit(); // �\��

	void LoadData();

	// �Q�[���Ր��@������
	void DimensionInit(int posx, int posy, int sizex, int sizey);

	// �Ֆʏ�����
	// playerColor�FBlack:�v���C���[��s, White:AI��s
	// StartMenuScreen�ŌĂ΂��
	void BoardInit(enum PieceColor playerColor);

	void ProcessInput();	// ���͏��� �|�[�����O�̌�ɌĂ΂��
	void Update();			// �Q�[���X�V ������

	void Draw();			// �`��
	void DrawTexture();		// �摜�`��
	void DrawScreenText();  // ������`��

private:
	// [y][x]
	int mBoard[8][8]; // �Ֆʏ�� 0:��Ȃ� 1,2:�e�v���C���[�̋����
	enum Player mNowPlayer; // ���݂̎��(1: �v���C���[, 2: CP)
	enum PieceColor mPlayerColor; // �v���C���[�̐F
	
	bool Play(int y, int x, bool isThink) { return true; } // ���ł�
	bool CheckGameEnd() { return true; } // �Q�[�����I����������`�F�b�N

	bool mIsClicked; // �{�[�h���N���b�N���ꂽ��

	// �摜
	Texture* BGTex;
	Texture* BlackTex;
	Texture* WhiteTex;

	// �ʒu, �T�C�Y
	Vector2 mPos;
	Vector2 mSize;

	Game* mGame; // �Q�[���ւ̎Q��
	InputSystem* mInputSystem;
};
