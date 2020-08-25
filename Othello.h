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
		eNone = -1, // �����Ȃ����
		eBlack = 0, // ��s
		eWhite = 1// ��U
	};

	enum Player{
		ePlayer,
		eAI
	};

	void Init(Game* game); // �摜�ȂǑS�̏�����, Game�S�̂̏������ŌĂ΂��
	void FlagInit();		// �e��t���O������
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
	void Update();			// �Q�[���X�V

	void Draw();			// �`��
	void DrawTexture();		// �摜�`��
	void DrawScreenText();  // ������`��
	int mBlackPoint, mWhitePoint;

	bool CheckGameEnd(); // �Q�[�����I����������`�F�b�N

private:
	// [y][x]
	int mBoard[8][8]; // �Ֆʏ�� -1:��Ȃ� 0,1:�e�v���C���[�̋����.
	enum Player mNowPlayer; // ���݂̎��
	enum PieceColor mPlayerColor; // �v���C���[�̐F
	enum PieceColor mAIColor; // AI�̐F

	int mPassCount; // �A������p�X�̉�
	
	int mPlayPointX, mPlayPointY; // �ł��ꂽ��̈ʒu
	void CalcPoint(const Vector2 &pt); // �N���b�N�ʒu���}�X�̍��W�ɕϊ�
	
	void ChangePieceNum(int color, int point);
	void ChangeTurn(); // �^�[�����
	bool ContainsPoint(const Vector2 &pt); // pt�����W���{�[�h�Ɋ܂܂�邩
	bool mIsClicked; // �{�[�h���N���b�N���ꂽ��
	int Play(int x, int y, int player, bool isThink); // ���ł�
	bool CheckPass(int board[8][8], int player);

	// AI
	OthelloAI mOthelloAI;

	// �摜
	Texture* BGTex;
	Texture* BlackTex;
	Texture* WhiteTex;

	// �\������

	// �ʒu, �T�C�Y
	Vector2 mPos;
	Vector2 mSize;

	Game* mGame; // �Q�[���ւ̎Q��
	InputSystem* mInputSystem;
};
