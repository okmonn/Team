#include "Enemy1.h"
#include "../Application/Application.h"

// �R���X�g���N�^
Enemy1::Enemy1(std::weak_ptr<Application> app, const Vec2f & pos, const Vec2f & size)
{
	this->app  = app;
	this->pos  = pos;
	this->size = size;
}

// �f�X�g���N�^
Enemy1::~Enemy1()
{
}

// �`��
void Enemy1::Draw(void)
{
}

// ����
void Enemy1::UpData(void)
{
}
