#pragma once
#include<string>

class Texture
{
public:
	// �R���X�g���N�^�ŉ摜�������߂�
	Texture(const std::string& graphname) :mGraphName(graphname){}
	~Texture(); // 

	bool Load(const std::string& filename);
	void UnLoad(); // ����͎g��Ȃ�

	// �摜�̕`�� 
	// ����x, y: ����̍��W 
	// sizeX, sizeY: �`�悵�����T�C�Y
	void Draw(int x, int y, int sizeX, int sizeY);

private:
	const std::string& mGraphName; // �摜�I�u�W�F�N�g�̖��O
	int GrHandle; // �O���t�B�b�N�n���h�� 
	int mWidth, mHeight; // �摜�̃T�C�Y
};