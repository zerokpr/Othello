#include"Button.h"
#include"Font.h"
#include"ScreenText.h"
#include"Texture.h"
#include "UIScreen.h"
#include "Game.h"

UIScreen::~UIScreen() {
	// �{�^������
	for (auto b : mButtons) {
		delete b.second;
	}

	// �e�L�X�g����
	for (auto text : mScreenTexts) {
		delete text.second;
	}
}

void UIScreen::ProcessInput() {

	// ���͂̃|�[�����O��ɌĂ΂��
	// �e�{�^���ɂ��ē��͏���
	ButtonProcessInput();

	// �L�[�{�[�h����(����)
}

void UIScreen::ButtonProcessInput(void) {
	for (auto b : mButtons) {
		if (b.second->ContainsPoint(mInputSystem->mMouseState.MousePos())) { // �J�[�\���|�C���^���{�^���̏�ɂ���
			// �n�C���C�g�i�������邩�͖��m��j
			b.second->SetHighlight(true);
			// �n�C���C�g����������Ȃ�A
			// �����ȃ{�^���ɂ��Ă̓n�C���C�g�����Ȃ��悤�ɂ���(Draw�Ŏ�������΂悢)

			if (mInputSystem->mMouseState.wasClicked()) { // �N���b�N����Ă���Ƃ�
				b.second->OnClick(); // �����ȃ{�^���ɂ��Ă͌Ăяo���Ă������N����Ȃ��悤�Ƀ{�^�����őΏ�
				mInputSystem->mMouseState.ClickEventEnd(); // �N���b�N�C�x���g�������ŏI��������B
			}
		}
		else {
			b.second->SetHighlight(false);
		}
	}
}

void UIScreen::Update() {
}

void UIScreen::Draw() {

	// �w�i�ȂǕ`��
	DrawTexture();

	// �{�^���`��
	DrawButtons();

	// �e�L�X�g�`��
	DrawScreenText();

}

void UIScreen::DrawTexture() {
	mBGTexture->Draw(0, 0, mGame->mScreenSizeX, mGame->mScreenSizeY); // �w�i�`��(�ύX�\��)
}

void UIScreen::DrawButtons(void) {
	for (auto b : mButtons) {
		b.second->Draw(); // �����ȃ{�^��(ry
	}
}

void UIScreen::DrawScreenText(void) {
	if (!mScreenTexts.empty()) {
		for (auto text : mScreenTexts) {
			text.second->Draw();
		}
	}
}

void UIScreen::AddButton(
	const std::string& buttonName, // �{�^������
	std::function<void()> onClick, // �R�[���o�b�N�֐�
	const Vector2& pos, const Vector2& dims, // �{�^���̐��@
	Texture* normalTex, Texture* highlightedTex, // �{�^���̉摜�iGame�N���X�ō폜�j
	bool isActivated,
	Font* font // �{�^���̃t�H���g�i�w�肵�Ȃ����UIScreen�̃f�t�H���g�̃t�H���g������j
) {
	if (font == nullptr) font = mFont;

	if (mButtons.find(buttonName) != mButtons.end()) { // ���ɓ����{�^�������݂���ꍇ
		printfDx("�{�^����: %s �̃{�^���͊��ɑ��݂��܂�\n", buttonName.c_str());
	}
	else {
		Button* button = new Button(
			buttonName,
			font,
			onClick,
			pos, dims,
			normalTex, highlightedTex,
			isActivated
		);
		mButtons.emplace(buttonName, button);
	}
}

Button* UIScreen::GetButton(const std::string& buttonName) {
	auto iter = mButtons.find(buttonName);
	if (iter != mButtons.end()) {
		return iter->second;
	}
	else {
		printfDx("�{�^����: %s �̃{�^���̎擾�Ɏ��s���܂���\n", buttonName.c_str());
		return nullptr;
	}
}

ScreenText* UIScreen::GetScreenText(const std::string& textName) {
	auto iter = mScreenTexts.find(textName);
	if (iter != mScreenTexts.end()) {
		return iter->second;
	}
	else {
		printfDx("�e�L�X�g��: %s �̎擾�Ɏ��s���܂���\n", textName.c_str());
		return nullptr;
	}
}

void UIScreen::AddScreenText(
	const std::string& textName,// �e�L�X�g����
	const std::string& text,	// �e�L�X�g���e
	Vector2 pos,				// �`��ꏊ
	int pointSize,				// �e�L�X�g�̕����T�C�Y
	Vector3 color,				// �`��F
	Font* font = nullptr		// �t�H���g�ւ̃|�C���^
) {
	if (mScreenTexts.find(textName) == mScreenTexts.end()) return;
	if (font == nullptr) font = mFont;
	ScreenText * Text = new ScreenText(
		text,
		pos,
		pointSize,
		color,
		font
	);
	mScreenTexts.emplace(textName, Text);
}