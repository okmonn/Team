#include "Player.h"
#include "../Application/Application.h"

// �R���X�g���N�^
Player::Player(std::weak_ptr<Application>app)
{
	this->app = app;
}

// �f�X�g���N�^
Player::~Player()
{
	Delete();
}

// �`��
void Player::Draw(void)
{
}

// ����
void Player::UpData(void)
{
}
