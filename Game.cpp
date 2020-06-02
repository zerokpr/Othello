#include "Game.h"

Game::Game(){

}

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
	// mPaused = PausedMenuScreen(this, &mInputSystem);				// ������
	// mResultMenu = ResultMenuScreen(this, &mInputSystem);			// ������

	// Othello������
	// mOthello.Init();

	return true;
}

void Game::LoadData() {
	// �摜�t�@�C���ǂݍ���
	AddTexture("NormalButton", "Button.jpg");	// �ʏ�{�^��
	AddTexture("HighlightedButton", "Button.jpg");				// �{�^���n�C���C�g
	/* �w�i�摜 */
	AddTexture("StartMenuBG", "ScreenBG.jpg"); // �X�^�[�g���j���[�w�i
	AddTexture("PlayingBG", "ScreenBG.jpg");   // �v���C�w�i
	// �|�[�Y���j���[�w�i
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
	WaitTimer(5000);
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
	// �N���b�N�C�x���g
	mInputSystem.Polling();

	/* �e�I�u�W�F�N�g�ɓ`�B */
	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.ProcessInput();
		break;
	case ePlaying:
		mPlaying.ProcessInput();	// ������
		break;
	case ePaused:
		//mPaused.ProcessInput();		// ������
		break;
	case eResultMenu:
		//mResultMenu.ProcessInput(); // ������
		break;
	default:						// �G���[����
		mIsRunning = false;
		break;
	}

}

void Game::GameUpdate() {

	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.Update(); // ������
		break;
	case ePlaying:
		//mOthello.Update(); // �Q�[�����[�h��������Ȃ�
		mPlaying.Update(); // ������ 
		break;
	case ePaused:
	//	mPaused.Update(); // ������
		break;
	case eResultMenu:
		//mResultMenu.Update(); // ������
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
		//mOthello.Draw();
		break;
	case ePaused:
		// mPaused.Draw();
		break;
	case eResultMenu:
		// mResultMenu.Draw();
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
		printfDx("�e�N�X�`���� %s �͊��ɑ��݂��܂�\n", texName);
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
		printfDx("�e�N�X�`���� %s �͑��݂��܂���\n", texName);
		QuitGame();
		return nullptr;
	}
}