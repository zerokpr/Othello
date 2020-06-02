#include "Game.h"

Game::Game(){

}

bool Game::Initialize() {

	if (DxLib_Init() == -1) { // DxLib初期化処理
		return false;
	}

	mIsRunning = true;
	
	// ゲームモードをスタート画面に設定
	mGameMode = Game::eStartMenu;

	// 画面モード設定
	ChangeWindowMode(true); // ウインドウモード
	SetGraphMode(800, 600, 32);
	SetMouseDispFlag(TRUE);

	LoadData(); // データロード

	// 画面サイズ取得
	GetScreenState(&mScreenSizeX, &mScreenSizeY, &mColorBitDepth);

	// InputSystem初期化
	mInputSystem.Init(this);

	// UIScreen初期化
	mStartMenu.Init(this);
	mPlaying.Init(this);
	// mPaused = PausedMenuScreen(this, &mInputSystem);				// 未実装
	// mResultMenu = ResultMenuScreen(this, &mInputSystem);			// 未実装

	// Othello初期化
	// mOthello.Init();

	return true;
}

void Game::LoadData() {
	// 画像ファイル読み込み
	AddTexture("NormalButton", "Button.jpg");	// 通常ボタン
	AddTexture("HighlightedButton", "Button.jpg");				// ボタンハイライト
	/* 背景画像 */
	AddTexture("StartMenuBG", "ScreenBG.jpg"); // スタートメニュー背景
	AddTexture("PlayingBG", "ScreenBG.jpg");   // プレイ背景
	// ポーズメニュー背景
	// リザルトメニュー背景

	// フォントデータ読み込み
	AddFont("default"); // 基本フォント
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

	for (auto font : mFonts) delete font.second;  // Fontクラスdelete
	if (InitFontToHandle() == -1) {				  // 作成したフォント削除
		printfDx("フォントデータ削除でエラー発生しました\n");
	}

	for (auto tex : mTextures) delete tex.second; // Textureクラスdelete
	if (InitGraph() == -1) {
		printfDx("画像データ削除でエラー発生しました\n");
	}
	DxLib_End();
}

void Game::ProcessInput() {

	/* イベント発生監視 */
	// クリックイベント
	mInputSystem.Polling();

	/* 各オブジェクトに伝達 */
	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.ProcessInput();
		break;
	case ePlaying:
		mPlaying.ProcessInput();	// 未実装
		break;
	case ePaused:
		//mPaused.ProcessInput();		// 未実装
		break;
	case eResultMenu:
		//mResultMenu.ProcessInput(); // 未実装
		break;
	default:						// エラー発生
		mIsRunning = false;
		break;
	}

}

void Game::GameUpdate() {

	switch (mGameMode) {
	case eStartMenu:
		mStartMenu.Update(); // 未実装
		break;
	case ePlaying:
		//mOthello.Update(); // ゲームモード実装するなら
		mPlaying.Update(); // 未実装 
		break;
	case ePaused:
	//	mPaused.Update(); // 未実装
		break;
	case eResultMenu:
		//mResultMenu.Update(); // 未実装
		break;
	default: // エラー発生
		mIsRunning = false;
		break;
	}
}

void Game::GenerateOutput() {

	// BGM

	// 描画
	// バッファクリア
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
	default: // エラー発生
		mIsRunning = false;
		break;
	}

	// 背景バッファ入れ替え
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
	if (iter != mFonts.end()) { // ロード済み
		if (iter->second->Load(fontName, size) ) { // 合うサイズが存在するか調べ、なければロード
			return iter->second;
		}
		else { // サイズがないので失敗
			return nullptr;
		}
	} else {					   // ロードしてなかった場合
		Font* font = new Font(fontName);
		if (font->Load(fontName, size) == false) { // フォントロード失敗
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
		printfDx("テクスチャ名 %s は既に存在します\n", texName);
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
		printfDx("テクスチャ名 %s は存在しません\n", texName);
		QuitGame();
		return nullptr;
	}
}