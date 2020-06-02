#pragma once
#include<string>
#include<unordered_map>
#include"Vector.h"

// Font�폜�̐ӔC��Game�N���Xs
class Font
{
public:
	Font(const std::string& fontName):mFontName(fontName) {}; // �K�v�ȃt�H���g�T�C�Y�����炩���ߓn��

	bool Load(const std::string& fontName, int pointSize);
	void UnLoad(); // ����̓t�H���g�f�[�^�ꊇ�폜���\�Ȃ̂Ŏg���K�v�͂Ȃ����A
	// SDL�ɐ؂�ւ���Ȃ炱���̎������K�v
	
	// �������`��
	// �w��T�C�Y�̃t�H���g���Ȃ���΃��[�h���Ă���`��A���[�h���s�Ȃ�false���Ԃ�
	bool Draw(
		int x, int y, 
		const std::string& text,
		const Vector3& color = {255,255,255},
		int pointSize = 30
	);

private:
	const std::string mFontName;
	std::unordered_map<int, int> mFontData; // �|�C���g�T�C�Y�ƃt�H���g�n���h���̘A�z�z��
};