#pragma once
#include<string>
#include"Font.h"
#include"Game.h"
#include"Vector.h"

// ScreenText
class ScreenText
{
public:
	ScreenText(
		const std::string& text,	// �e�L�X�g���e
		Vector2 pos,				// �`��ꏊ
		int pointSize,				// �e�L�X�g�̕����T�C�Y
		Vector3 color,				// �`��F
		Font* font					// �t�H���g�ւ̃|�C���^
	): mText(text), mPos(pos), mPointSize(pointSize), mColor(color), mFont(font){}
	~ScreenText(){}

	// �������`��
	void Draw(void);

private:
	std::string mText; // �`��e�L�X�g
	int mPointSize;    // �`��|�C���g
	Vector2 mPos;  // �`��ꏊ
	Vector3 mColor;    // �`��F
	Font* mFont; // �`��t�H���g
	bool mIsActivated; // ���̃e�L�X�g���L����
};