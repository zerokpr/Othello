#pragma once
#include"UIScreen.h"

// �v���C��ʂ̓��A�I�Z���ՈȊO�̋@�\
// 
class PlayingScreen : public UIScreen
{
public:
	virtual void Init(class Game* game);
	virtual void FontInit(); // �t�H���g�w��
	virtual void ScreenTextInit();
	virtual void ButtonInit();
	virtual void TextureInit();
	// virtual void ProcessInput();
	// virtual void Update();
	// virtual void Draw();

private:

};