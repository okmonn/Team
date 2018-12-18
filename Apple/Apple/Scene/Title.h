#pragma once
#include "Scene.h"
#include <map>
#include <string>

class Title :
	public Scene
{
public:
	// �R���X�g���N�^
	Title(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Title();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:
	// ��`���̃t�@�C���̍쐬
	int CreateInfo(const std::string& fileName);
	// �A�j���[�V��������p�J�E���^
	// ~-1 ��`��A 0~ �J�E���^��0�ɂȂ�܂Ō��Z�𑱂���
	
	std::map<std::string,int> animCnt;
};

