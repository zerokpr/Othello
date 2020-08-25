#pragma once
#include<functional>
#include<unordered_map>
#include<string>
#include"Vector.h"
#include"ScreenText.h"

// �O���錾
class InputSystem;
// ���̃N���X���p��
// ���̃N���X�̓R�s�[�s��
class UIScreen {
public:
	UIScreen(){}
	virtual ~UIScreen();
	
	// UIScreen�̔h���N���X�͈ȉ����I�[�o�[���C�h�o����
	// �������z�֐�
	virtual void Init(class Game* game) = 0;  // ����������
	virtual void FontInit() = 0;
	virtual void ButtonInit() = 0;		// �{�^��������������
	virtual void ScreenTextInit() = 0;	// �e�L�X�g�f�[�^������������
	virtual void TextureInit() = 0;		// �摜������������

	// �I�[�o�[���C�h�\�ȈĐ�
	void ProcessInput();	// ���͂̃|�[�����O��ɌĂ΂��
	void Update();			// �����g��Ȃ�
	void Draw();			// �`�悷��

	// �Q�[����Ԃւ̎Q��
	class Game* mGame;

	// ���̓V�X�e���ւ̎Q��
	class InputSystem* mInputSystem;

	// �t�H���g�ւ̎Q��
	// �f�t�H���g�Ŏg�p����t�H���g�������Ă����A�K�v����Ŋe�\���v�f�ɓn���t�H���g�̎�ނ�ς���
	class Font* mFont;
	
	// �X�N���[�������{�^��
	std::unordered_map<std::string, class Button*> mButtons;
	// �{�^����ǉ�
	void AddButton(
		const std::string& buttonName, // �{�^������
		std::function<void()> onClick, // �R�[���o�b�N�֐�
		const Vector2& pos, const Vector2& dims, // �{�^���̐��@
		class Texture* normalTex, class Texture* highlightedTex, // �{�^���̉摜�iGame�N���X�ō폜�j
		bool isActivated = true, // �ŏ��Ƀ{�^����L�������邩�i�f�t�H���g����true�j
		class Font* font = nullptr// �{�^���̃t�H���g�i�w�肵�Ȃ����UIScreen�̃f�t�H���g�̃t�H���g������j
	);
	// �{�^�����̂ł��̃{�^���ւ̃|�C���^�𓾂�
	class Button* GetButton(const std::string& buttonName);
	void DrawButtons(void);

	// �摜�f�[�^
	class Texture* mBGTexture;
	void DrawTexture(void); // �摜��`�悷��w���p�[�֐�

	// �\���e�L�X�g�Q
	std::unordered_map<std::string, class ScreenText*> mScreenTexts;
	void AddScreenText(
		const std::string& textName, // �e�L�X�g��
		const std::string& text,	// �e�L�X�g���e
		Vector2 pos,				// �`��ꏊ
		int pointSize,				// �e�L�X�g�̕����T�C�Y
		Vector3 color,				// �`��F
		class Font* font = nullptr		// �t�H���g�ւ̃|�C���^
	);

	class ScreenText* GetScreenText(const std::string& textName);
	void DrawScreenText(void); // �e�L�X�g��`�悷��w���p�[�֐�

	void ButtonProcessInput(); // �{�^�����͂̃w���p�|�֐�
	
};
