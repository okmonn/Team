#include "Enemy.h"
#include "Player.h"
#include "../Application/Application.h"
#include <random>

// �R���X�g���N�^
Enemy::Enemy() : 
	target(0.0f)
{
}

// �f�X�g���N�^
Enemy::~Enemy()
{
}

// �����_���ȃ^�[�Q�b�g���W�̐���
Vec2f Enemy::GetRandomPos(const Vec2f & range)
{
	std::random_device dev;
	std::mt19937 mt(dev());

	//�����_���͈�
	std::uniform_real_distribution<float> offsetX(0.0f, range.x);
	std::uniform_real_distribution<float> offsetY(0.0f, range.y);


	return Vec2f(offsetX(mt), offsetY(mt));
}

// �����蔻��
bool Enemy::CheckHit(void)
{
	return false;
}
