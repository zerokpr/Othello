#pragma once
#include<string>
#include<functional>
#include"Vector.h"
#include"Texture.h"
#include"Font.h"

// �{�^���폜�͊eUIScreen�̐ӔC
class Button
{
public:
	// �R���X�g���N�^�[
	// �{�^�����́A�t�H���g�A�R�[���o�b�N�֐��A�{�^���̈ʒu�A���@�A�{�^���̉摜�ւ̃|�C���^���󂯎��
	Button(
		const std::string& name, // �{�^������
		class Font* font,		// �t�H���g�ւ̎Q��
		std::function<void()> onClick, // �R�[���o�b�N�֐�
		const Vector2& pos,			// �{�^���̈ʒu
		const Vector2& size,		// �{�^���̃T�C�Y
		Texture* normalTex, Texture* highlightedTex,	// �{�^���摜�ւ̃|�C���^
		bool activated = true
	) :
		mName(name),
		mFont(font),
		mOnClick(onClick),
		mPosition(pos), mSize(size),
		mNormalTex(normalTex), mHighlightedTex(highlightedTex),
		mIsActivated(activated)
	{}

	// �^����ꂽ���Wpt���{�^���͈͓̔��Ȃ�true��Ԃ�
	bool ContainsPoint(const Vector2& pt);
	
	// �R�[���o�b�N�֐�
	void OnClick();

	// �n�C���C�g��t����
	// ����t��true�Ȃ�n�C���C�g������Afalse�Ȃ�O��
	void SetHighlight(bool t) { mHighlighted = t; }

	// �{�^���̗L����ύX����
	void Activate(bool t) { mIsActivated = t; }
	// �{�^���̏�Ԃ��m�F����
	bool IsActivated(void) { return mIsActivated; }

	// �`��
	void Draw(void); // ������

private:
	// �R���X�g���N�^�œn�������
	std::string mName; // �{�^���̖��O
	Font* mFont; // �{�^���̖��O�̃t�H���g
	std::function<void()> mOnClick; // �R�[���o�b�N�֐�
	Vector2 mPosition; // �{�^���̐�Έʒu(����p�̍��W)
	Vector2 mSize; // �{�^���̃T�C�Y
	Texture* mNormalTex; // �W���{�^���摜
	Texture* mHighlightedTex; // �n�C���C�g�t���{�^���摜 

	bool mHighlighted; // �n�C���C�g��t���邩
	bool mIsActivated; // �{�^�����L����
};