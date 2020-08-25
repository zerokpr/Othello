#pragma once
#include<functional>
#include<unordered_map>
#include<string>
#include"Vector.h"
#include"ScreenText.h"

// 前方宣言
class InputSystem;
// このクラスを継承
// このクラスはコピー不可
class UIScreen {
public:
	UIScreen(){}
	virtual ~UIScreen();
	
	// UIScreenの派生クラスは以下をオーバーライド出来る
	// 純粋仮想関数
	virtual void Init(class Game* game) = 0;  // 初期化する
	virtual void FontInit() = 0;
	virtual void ButtonInit() = 0;		// ボタンを初期化する
	virtual void ScreenTextInit() = 0;	// テキストデータを初期化する
	virtual void TextureInit() = 0;		// 画像を初期化する

	// オーバーライド可能な案数
	void ProcessInput();	// 入力のポーリング後に呼ばれる
	void Update();			// 多分使わない
	void Draw();			// 描画する

	// ゲーム状態への参照
	class Game* mGame;

	// 入力システムへの参照
	class InputSystem* mInputSystem;

	// フォントへの参照
	// デフォルトで使用するフォントを持っておき、必要次第で各構成要素に渡すフォントの種類を変える
	class Font* mFont;
	
	// スクリーンが持つボタン
	std::unordered_map<std::string, class Button*> mButtons;
	// ボタンを追加
	void AddButton(
		const std::string& buttonName, // ボタン名称
		std::function<void()> onClick, // コールバック関数
		const Vector2& pos, const Vector2& dims, // ボタンの寸法
		class Texture* normalTex, class Texture* highlightedTex, // ボタンの画像（Gameクラスで削除）
		bool isActivated = true, // 最初にボタンを有効化するか（デフォルトだとtrue）
		class Font* font = nullptr// ボタンのフォント（指定しなければUIScreenのデフォルトのフォントが入る）
	);
	// ボタン名称でそのボタンへのポインタを得る
	class Button* GetButton(const std::string& buttonName);
	void DrawButtons(void);

	// 画像データ
	class Texture* mBGTexture;
	void DrawTexture(void); // 画像を描画するヘルパー関数

	// 表示テキスト群
	std::unordered_map<std::string, class ScreenText*> mScreenTexts;
	void AddScreenText(
		const std::string& textName, // テキスト名
		const std::string& text,	// テキスト内容
		Vector2 pos,				// 描画場所
		int pointSize,				// テキストの文字サイズ
		Vector3 color,				// 描画色
		class Font* font = nullptr		// フォントへのポインタ
	);

	class ScreenText* GetScreenText(const std::string& textName);
	void DrawScreenText(void); // テキストを描画するヘルパー関数

	void ButtonProcessInput(); // ボタン入力のヘルパ－関数
	
};
