#pragma once
#include<string>
#include<functional>
#include"Vector.h"
#include"Texture.h"
#include"Font.h"

// ボタン削除は各UIScreenの責任
class Button
{
public:
	// コンストラクター
	// ボタン名称、フォント、コールバック関数、ボタンの位置、寸法、ボタンの画像へのポインタを受け取る
	Button(
		const std::string& name, // ボタン名称
		class Font* font,		// フォントへの参照
		std::function<void()> onClick, // コールバック関数
		const Vector2& pos,			// ボタンの位置
		const Vector2& size,		// ボタンのサイズ
		Texture* normalTex, Texture* highlightedTex,	// ボタン画像へのポインタ
		bool activated = true
	) :
		mName(name),
		mFont(font),
		mOnClick(onClick),
		mPosition(pos), mSize(size),
		mNormalTex(normalTex), mHighlightedTex(highlightedTex),
		mIsActivated(activated)
	{}

	// 与えられた座標ptがボタンの範囲内ならtrueを返す
	bool ContainsPoint(const Vector2& pt);
	
	// コールバック関数
	void OnClick();

	// ハイライトを付ける
	// 引数tがtrueならハイライトをつける、falseなら外す
	void SetHighlight(bool t) { mHighlighted = t; }

	// ボタンの有効を変更する
	void Activate(bool t) { mIsActivated = t; }
	// ボタンの状態を確認する
	bool IsActivated(void) { return mIsActivated; }

	// 描画
	void Draw(void); // 未実装

private:
	// コンストラクタで渡される情報
	std::string mName; // ボタンの名前
	Font* mFont; // ボタンの名前のフォント
	std::function<void()> mOnClick; // コールバック関数
	Vector2 mPosition; // ボタンの絶対位置(左上角の座標)
	Vector2 mSize; // ボタンのサイズ
	Texture* mNormalTex; // 標準ボタン画像
	Texture* mHighlightedTex; // ハイライト付きボタン画像 

	bool mHighlighted; // ハイライトを付けるか
	bool mIsActivated; // ボタンが有効か
};