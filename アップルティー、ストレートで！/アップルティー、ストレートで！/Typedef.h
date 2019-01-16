#pragma once
#include "etc/Vector2.h"
#include <string>
#include <vector>

// �_�~�[�p�\����
struct Dummy {
	//���W
	Vec2 pos;
	//�T�C�Y
	Vec2 size;
};

// �A�j���[�V�����E��`���
struct Info {
	//�X�e�[�^�X���̕�����
	unsigned char stNameNum;
	//�X�e�[�^�X��
	std::string state;
	//�A�j���[�V��������
	float animTime;
	//�A�j���[�V������
	unsigned char animNum;
	//��`���
	std::vector<Dummy>rect;
};

// �A�j���[�V�����E��`���
struct Rect {
	//���W
	Vec2f pos;
	//�T�C�Y
	Vec2f size;
};
