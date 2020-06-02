#include "Font.h"
#include"DxLib.h"

bool Font::Load(const std::string& fontName, int pointSize = 30) {
	
	if (fontName == "default") {
		int fontHandle = CreateFontToHandle(NULL, pointSize, -1, -1);
		mFontData.emplace(pointSize, fontHandle);
		return true;
	}

	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end()) { // ��������Load�̕K�v�Ȃ�
		return true;
	}
	
	// �T�C�Y���Ƀt�H���g��ǂݍ���
	int fontHandle = CreateFontToHandle(fontName.c_str(), pointSize, -1, -1);
	if (fontHandle == -1) { // �ǂݍ��ݎ��s
		printfDx("�t�H���g %s, �T�C�Y %d �̃��[�h�Ɏ��s���܂���\n", fontName, pointSize);
		return false;
	}
	mFontData.emplace(pointSize, fontHandle);
	return true;
}

void Font::UnLoad() {
	for (auto fontdata : mFontData) {
		DeleteFontToHandle(fontdata.second);
	}
}

bool Font::Draw(
	int x, int y,
	const std::string& text,
	const Vector3& color,
	int pointSize) {
	
	if (mFontData.find(pointSize) == mFontData.end()) { // �w��T�C�Y���Ȃ��ꍇ
		if (!Load(mFontName, pointSize)) {
			return false;
		}
	}

	DrawStringToHandle(
		x, y, 
		text.c_str(), 
		GetColor(color.x, color.y, color.z),
		mFontData[pointSize]
	); // �`��
	
	return true;
}