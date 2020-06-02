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


// ゲーム全体の管理をする
// 各種データの削除の責任を持つ
class Othello;
class Game {
public:

	bool Initialize();	// 初期化
	void LoadData();	// Initialize内で最初に呼ぶ
	void MainLoop();	// ゲームのメインループ
	void Shutdown();	// ゲーム終了処理

	Game(); // 
	~Game() {} // デストラクタ

	enum GameMode {
		eStartMenu,
		ePlaying,
		ePaused,
		eResultMenu
	};

	// ゲームモード変更
	void SetGameMode(enum GameMode gamemode);

	// ゲーム終了関数
	void QuitGame();

	// MainLoop内の関数群
	void ProcessInput(); // 入力処理
	void GameUpdate(); // ゲーム世界更新
	void GenerateOutput(); // 各種出力

	// 入力管理
	class InputSystem mInputSystem;

	// オセロの状態保持
	Othello mOthello;

	// モード毎の画面表示
	StartMenuScreen mStartMenu;
	PlayingScreen mPlaying;
	// PausedMenuScreen mPaused;
	// ResultMenuScreen mResultMenu;

	// 音響管理

	// フォントデータ
	// ポインタが指すフォントデータの破棄はGame::Shutdownで行われる
	std::unordered_map<std::string, Font*> mFonts;
	// 指定のサイズと形式を持つフォントを取得する
	// fontNameで指定したフォント名、サイズのフォントが既に読み込まれているかを確認、
	// 読み込まれていなければ読み込み、読み込まれていればそのままポインタを返す
	// フォント名がDxlibのサポートしていないものだとnullptrを返す
	Font* AddFont(const std::string& fontName, int size = 30);	// 余裕があったらGetFontの実装

	// 画像データ
	// ポインタが指す画像データの破棄はGame::Shutdownで行われる
	std::unordered_map<std::string, Texture*> mTextures;
	// 指定の画像を取得する
	void AddTexture(const std::string& texName, const std::string& filename);
	Texture* GetTexture(const std::string& texName);
	// 

	// 画面全体のサイズを持つ情報
	int mScreenSizeX, mScreenSizeY;
	// 画面のカラービット深度
	int mColorBitDepth;

private:
	// ゲームモード
	enum GameMode mGameMode;

	// ゲームを続行するか
	bool mIsRunning;
};