#pragma once
#include<string>
#include"Font.h"
#include"Game.h"
#include"Vector.h"

// ScreenText
class ScreenText
{
public:
	ScreenText(
		const std::string& text,	// テキスト内容
		Vector2 pos,				// 描画場所
		int pointSize,				// テキストの文字サイズ
		Vector3 color,				// 描画色
		Font* font					// フォントへのポインタ
	): mText(text), mPos(pos), mPointSize(pointSize), mColor(color), mFont(font){}
	~ScreenText(){}

	// 文字列を描画
	void Draw(void);

private:
	std::string mText; // 描画テキスト
	int mPointSize;    // 描画ポイント
	Vector2 mPos;  // 描画場所
	Vector3 mColor;    // 描画色
	Font* mFont; // 描画フォント
	bool mIsActivated; // このテキストが有効か
};