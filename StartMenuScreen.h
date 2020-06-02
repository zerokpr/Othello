#pragma once
#include "UIScreen.h"

class StartMenuScreen : public UIScreen
{
public:
	StartMenuScreen();
	~StartMenuScreen();

	virtual void Init(class Game* game);
	virtual void FontInit(); // �t�H���g�w��
	virtual void ScreenTextInit();
	virtual void ButtonInit();
	virtual void TextureInit();
	// virtual void ProcessInput();
	// virtual void Update();
	// virtual void Draw();

private:

	// �{�^���ŃQ�[�����[�h�����߂�
	enum StartMenuState {	// 
		eStartMenu,			// �X�^�[�g���
		eModeSelect,		// ���[�h�I���i�������A�I�Z���ȊO���I���ł���悤�ɂ���Ȃ�A�������j
		eFirstPlayerSelect,	// ��ԑI�����
		eExit				// �Q�[���ޏo�I�����
	} mStartMenuMode;
};