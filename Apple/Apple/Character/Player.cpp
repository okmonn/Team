#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// �R���X�g���N�^
Player::Player(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// �f�X�g���N�^
Player::~Player()
{
}

// ����
void Player::UpData(void)
{
}

// �`��
void Player::Draw(void)
{
}
