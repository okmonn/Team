#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// �R���X�g���N�^
Player::Player(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;

	Load("rsc/img/player.png", "pl");
	LoadInfo("rsc/info/player.info");
}

// �f�X�g���N�^
Player::~Player()
{
}

// ����
void Player::UpData(void)
{
	Animator();
}

// �`��
void Player::Draw(void)
{
	DrawImg("pl", 0, 0, 240, 270);
}
