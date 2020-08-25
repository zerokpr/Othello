#include "Game.h"

bool Game::Initialize() {

	if (DxLib_Init() == -1) { // DxLib����������
		return false;
	}

	mIsRunning = true;
	
	// �Q�[�����[�h���X�^�[�g��ʂɐݒ�
	mGameMode = Game::eStartMenu;

	// ��ʃ��[�h�ݒ�
	ChangeWindowMode(true); // �E�C���h�E���[�h
	SetGraphMode(800, 600, 32);
	SetMouseDispFlag(TRUE);

	LoadData(); // �f�[�^���[�h

	// ��ʃT�C�Y�擾
	GetScreenState(&mScreenSizeX, &mScreenSizeY, &mColorBitDepth);

	// InputSystem������
	mInputSystem.Init(this);

	// UIScreen������
	mStartMenu.Init(this);
	mPlaying.Init(this);
	mPaused.Init(this);
	mResultMenu.Init(this);

	// Othello������
	mOthello.Init(this);

	return true;
}

void Game::LoadData() {
	// �摜�t�@�C���ǂݍ���
	AddTexture("NormalButton", "./img/Button.jpg");	// �ʏ�{�^��
	AddTexture("HighlightedButton", "./img/Button.jpg");				// �{�^���n�C���C�g
	/* �w�i�摜 */
	AddTexture("StartMenuBG", "./img/ScreenBG.jpg"); // �X�^�[�g���j���[�w�i
	AddTexture("PlayingBG", "./img/ScreenBG.jpg");   // �v���C�w�i
	AddTexture("PauseMenuBG", "./img/ScreenBG.jpg"); // �|�[�Y���j���[�w�i
	AddTexture("ResultMenuBG", "./img/ScreenBG.jpg"); // ���U���g��ʔq�[
	// ���U���g���j���[�w�i

	// �t�H���g�f�[�^�ǂݍ���
	AddFont("default"); // ��{�t�H���g
}

void Game::MainLoop() {
	while (ProcessMessage() == 0 && mIsRunning) {
		ProcessInput();
		GameUpdate();
		GenerateOutput();
	}
	WaitTimer(1000);
}

void Game::Shutdown() {

	for (auto font : mFonts) delete font.second;  // Font�N���Xdelete
	if (InitFontToHandle() == -1) {				  // �쐬�����t�H���g�폜
		printfDx("�t�H���g�f�[�^�폜�ŃG���[�������܂���\n");
	}

	for (auto tex : mTextures) delete tex.second; // Texture�N���Xdelete
	if (InitGraph() == -1) {
		printfDx("�摜�f�[�^�폜�ŃG���[�������܂���\n");
	}
	DxLib_End();
}

void Game::ProcessInput() {

	/* �C�x���g�����Ď� */
	// ���̓|�[�����O
	mInputSystem.Polling();

	/* �e�I�u�W�F�N�g���C�x���g�擾 */
	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.ProcessInput();
		break;
	case ePlaying:
		mOthello.ProcessInput();
		mPlaying.ProcessInput();
		break;
	case ePaused:
		mPaused.ProcessInput();
		break;
	case eResultMenu:
		mResultMenu.ProcessInput();
		break;
	default:						// �G���[����
		mIsRunning = false;
		break;
	}

}

void Game::GameUpdate() {

	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.Update();
		break;
	case ePlaying:
		mOthello.Update();
		mPlaying.Update();
		if (mOthello.CheckGameEnd()) {
			mGameMode = eResultMenu;
		}
		break;
	case ePaused:
		mPaused.Update();
		break;
	case eResultMenu:
		mResultMenu.Update();
		break;
	default: // �G���[����
		mIsRunning = false;
		break;
	}
}

void Game::GenerateOutput() {

	// BGM

	// �`��
	// �o�b�t�@�N���A
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.Draw();
		break;
	case ePlaying:
		mPlaying.Draw();
		mOthello.Draw();
		break;
	case ePaused:
		mPaused.Draw();
		break;
	case eResultMenu:
		mResultMenu.Draw();
		break;
	default: // �G���[����
		mIsRunning = false;
		break;
	}

	// �w�i�o�b�t�@����ւ�
	ScreenFlip();
}

void Game::SetGameMode(enum GameMode gamemode) {
	mGameMode = gamemode;
}

void Game::QuitGame() {
	mIsRunning = false;
}

Font* Game::AddFont(const std::string& fontName, int size) {

	auto iter = mFonts.find(fontName);
	if (iter != mFonts.end()) { // ���[�h�ς�
		if (iter->second->Load(fontName, size) ) { // �����T�C�Y�����݂��邩���ׁA�Ȃ���΃��[�h
			return iter->second;
		}
		else { // �T�C�Y���Ȃ��̂Ŏ��s
			return nullptr;
		}
	} else {					   // ���[�h���ĂȂ������ꍇ
		Font* font = new Font(fontName);
		if (font->Load(fontName, size) == false) { // �t�H���g���[�h���s
			printfDx("�t�H���g�� %s �̃��[�h�Ɏ��s���܂���\n", fontName.c_str());
			QuitGame();
			return nullptr;
		}
		else {
			mFonts.emplace(fontName, font);
			return font;
		}
	}
}

void Game::AddTexture(const std::string& texName, const std::string& fileName) {
	if (mTextures.find(texName) != mTextures.end()){
		printfDx("�e�N�X�`���� %s �͊��ɑ��݂��܂�\n", texName.c_str());
	} else {
		Texture* tex = new Texture(texName);
		if(tex->Load(fileName) == false) {
			QuitGame();
		}
		mTextures.emplace(texName, tex);
	}
}

Texture* Game::GetTexture(const std::string& texName) {
	auto iter = mTextures.find(texName);
	if (iter != mTextures.end()) {
		return iter->second;
	}else {
		printfDx("�e�N�X�`���� %s �͑��݂��܂���\n", texName.c_str());
		QuitGame();
		return nullptr;
	}
}