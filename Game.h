#pragma once
#include"DxLib.h"
#include"UIScreen.h"
#include"InputSystem.h"
#include"Othello.h"
#include"Font.h"
#include"Texture.h"
#include"StartMenuScreen.h"
#include"PlayingScreen.h"
//#include"PausedMenuScreen.h"
//#include"ResultMenuScreen.h"
#include<unordered_map>
#include<vector>
#include<string>


// �Q�[���S�̂̊Ǘ�������
// �e��f�[�^�̍폜�̐ӔC������
class Othello;
class Game {
public:

	bool Initialize();	// ������
	void LoadData();	// Initialize���ōŏ��ɌĂ�
	void MainLoop();	// �Q�[���̃��C�����[�v
	void Shutdown();	// �Q�[���I������

	Game(); // 
	~Game() {} // �f�X�g���N�^

	enum GameMode {
		eStartMenu,
		ePlaying,
		ePaused,
		eResultMenu
	};

	// �Q�[�����[�h�ύX
	void SetGameMode(enum GameMode gamemode);

	// �Q�[���I���֐�
	void QuitGame();

	// MainLoop���̊֐��Q
	void ProcessInput(); // ���͏���
	void GameUpdate(); // �Q�[�����E�X�V
	void GenerateOutput(); // �e��o��

	// ���͊Ǘ�
	class InputSystem mInputSystem;

	// �I�Z���̏�ԕێ�
	Othello mOthello;

	// ���[�h���̉�ʕ\��
	StartMenuScreen mStartMenu;
	PlayingScreen mPlaying;
	// PausedMenuScreen mPaused;
	// ResultMenuScreen mResultMenu;

	// �����Ǘ�

	// �t�H���g�f�[�^
	// �|�C���^���w���t�H���g�f�[�^�̔j����Game::Shutdown�ōs����
	std::unordered_map<std::string, Font*> mFonts;
	// �w��̃T�C�Y�ƌ`�������t�H���g���擾����
	// fontName�Ŏw�肵���t�H���g���A�T�C�Y�̃t�H���g�����ɓǂݍ��܂�Ă��邩���m�F�A
	// �ǂݍ��܂�Ă��Ȃ���Γǂݍ��݁A�ǂݍ��܂�Ă���΂��̂܂܃|�C���^��Ԃ�
	// �t�H���g����Dxlib�̃T�|�[�g���Ă��Ȃ����̂���nullptr��Ԃ�
	Font* AddFont(const std::string& fontName, int size = 30);	// �]�T����������GetFont�̎���

	// �摜�f�[�^
	// �|�C���^���w���摜�f�[�^�̔j����Game::Shutdown�ōs����
	std::unordered_map<std::string, Texture*> mTextures;
	// �w��̉摜���擾����
	void AddTexture(const std::string& texName, const std::string& filename);
	Texture* GetTexture(const std::string& texName);
	// 

	// ��ʑS�̂̃T�C�Y�������
	int mScreenSizeX, mScreenSizeY;
	// ��ʂ̃J���[�r�b�g�[�x
	int mColorBitDepth;

private:
	// �Q�[�����[�h
	enum GameMode mGameMode;

	// �Q�[���𑱍s���邩
	bool mIsRunning;
};