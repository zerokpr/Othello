#include<string.h>
#include"DxLib.h"
#include "Texture.h"


Texture::~Texture()
{
}

bool Texture::Load(const std::string& filename) {
	GrHandle = LoadGraph(filename.c_str());
	if (GrHandle < 0 || GetGraphSize(GrHandle, &mWidth, &mHeight) == -1) {
		printfDx("画像ファイル %s\nの読み込みに失敗しました\n", filename.c_str());
		return false;
	}
	// printfDx("画像ファイル %s を読み込みを完了\n", filename);
	return true;
}

void Texture::UnLoad() {
	DeleteGraph(GrHandle);
}

void Texture::Draw(int x, int y, int sizeX, int sizeY) {
	DrawExtendGraph(x, y, x+sizeX, y+sizeY, GrHandle, false);
}