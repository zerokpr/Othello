#include"Button.h"
#include"Font.h"
#include"ScreenText.h"
#include"Texture.h"
#include "UIScreen.h"
#include "Game.h"

UIScreen::~UIScreen() {
	// ボタン消去
	for (auto b : mButtons) {
		delete b.second;
	}

	// テキスト消去
	for (auto text : mScreenTexts) {
		delete text.second;
	}
}

void UIScreen::ProcessInput() {

	// 入力のポーリング後に呼ばれる
	// 各ボタンについて入力処理
	ButtonProcessInput();

	// キーボード入力(未定)
}

void UIScreen::ButtonProcessInput(void) {
	for (auto b : mButtons) {
		if (b.second->ContainsPoint(mInputSystem->mMouseState.MousePos())) { // カーソルポインタがボタンの上にある
			// ハイライト（実装するかは未確定）
			b.second->SetHighlight(true);
			// ハイライトを実装するなら、
			// 無効なボタンについてはハイライトがつかないようにする(Drawで実装すればよい)

			if (mInputSystem->mMouseState.wasClicked()) { // クリックされているとき
				b.second->OnClick(); // 無効なボタンについては呼び出しても何も起こらないようにボタン側で対処
				mInputSystem->mMouseState.ClickEventEnd(); // クリックイベントをここで終了させる。
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

	// 背景など描画
	DrawTexture();

	// ボタン描画
	DrawButtons();

	// テキスト描画
	DrawScreenText();

}

void UIScreen::DrawTexture() {
	mBGTexture->Draw(0, 0, mGame->mScreenSizeX, mGame->mScreenSizeY); // 背景描画(変更予定)
}

void UIScreen::DrawButtons(void) {
	for (auto b : mButtons) {
		b.second->Draw(); // 無効なボタン(ry
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
	const std::string& buttonName, // ボタン名称
	std::function<void()> onClick, // コールバック関数
	const Vector2& pos, const Vector2& dims, // ボタンの寸法
	Texture* normalTex, Texture* highlightedTex, // ボタンの画像（Gameクラスで削除）
	bool isActivated,
	Font* font // ボタンのフォント（指定しなければUIScreenのデフォルトのフォントが入る）
) {
	if (font == nullptr) font = mFont;

	if (mButtons.find(buttonName) != mButtons.end()) { // 既に同名ボタンが存在する場合
		printfDx("ボタン名: %s のボタンは既に存在します\n", buttonName.c_str());
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
		printfDx("ボタン名: %s のボタンの取得に失敗しました\n", buttonName.c_str());
		return nullptr;
	}
}

ScreenText* UIScreen::GetScreenText(const std::string& textName) {
	auto iter = mScreenTexts.find(textName);
	if (iter != mScreenTexts.end()) {
		return iter->second;
	}
	else {
		printfDx("テキスト名: %s の取得に失敗しました\n", textName.c_str());
		return nullptr;
	}
}

void UIScreen::AddScreenText(
	const std::string& textName,// テキスト名称
	const std::string& text,	// テキスト内容
	Vector2 pos,				// 描画場所
	int pointSize,				// テキストの文字サイズ
	Vector3 color,				// 描画色
	Font* font = nullptr		// フォントへのポインタ
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