#pragma once
#include "etc/Vector2.h"
#include <string>
#include <vector>

// ��`
template<typename T>
struct Rect {
	//���W
	T pos;
	//�T�C�Y
	T size;
};

// �������`�̎��
enum class HitType {
	//�_���[�W
	damage,
	//�U��
	attack
};

// �������`
template<typename T>
struct HitRect {
	//���
	HitType type;
	//��`
	Rect<T>rect;
};

// �A�j���[�V�����؂����`�E�������`
struct AnimHitRect {
	//�A�j���[�V������`
	Rect<Vec2f>anim;
	//�������`
	std::vector<HitRect<Vec2f>>hit;
};

// �A�j���[�V�����E��`���
struct Info {
	//�X�e�[�^�X
	std::string st;
	//�A�j���[�V�����ڍs�t���[��
	float animTime;
	//�A�j���[�V�����؂����`
	std::vector<AnimHitRect>rect;
};
