#pragma once
#include<string>
#include<unordered_map>
#include"Vector.h"

// Font削除の責任はGameクラスs
class Font
{
public:
	Font(const std::string& fontName):mFontName(fontName) {}; // 必要なフォントサイズをあらかじめ渡す

	bool Load(const std::string& fontName, int pointSize);
	void UnLoad(); // 今回はフォントデータ一括削除が可能なので使う必要はないが、
	// SDLに切り替えるならここの実装も必要
	
	// 文字列を描画
	// 指定サイズのフォントがなければロードしてから描画、ロード失敗ならfalseが返る
	bool Draw(
		int x, int y, 
		const std::string& text,
		const Vector3& color = {255,255,255},
		int pointSize = 30
	);

private:
	const std::string mFontName;
	std::unordered_map<int, int> mFontData; // ポイントサイズとフォントハンドルの連想配列
};