#pragma once
#include<string>

class Texture
{
public:
	// コンストラクタで画像名を決める
	Texture(const std::string& graphname) :mGraphName(graphname){}
	~Texture(); // 

	bool Load(const std::string& filename);
	void UnLoad(); // 今回は使わない

	// 画像の描画 
	// 引数x, y: 左上の座標 
	// sizeX, sizeY: 描画したいサイズ
	void Draw(int x, int y, int sizeX, int sizeY);

private:
	const std::string& mGraphName; // 画像オブジェクトの名前
	int GrHandle; // グラフィックハンドル 
	int mWidth, mHeight; // 画像のサイズ
};