#include "Enemy.h"

// �R���X�g���N�^
Enemy::Enemy()
{
}

// �f�X�g���N�^
Enemy::~Enemy()
{
}

// �ҋ@���̏���
void Enemy::Wait(void)
{
	if (st != "wait")
	{
		return;
	}
}

// �ړ����̏���
void Enemy::Walk(void)
{
	if (st != "walk")
	{
		return;
	}
}

// �U�����̏���
void Enemy::Attack(void)
{
	if (st != "attack")
	{
		return;
	}
}

// �_���[�W���̏���
void Enemy::Damage(void)
{
	if (st != "damage")
	{
		return;
	}
}
