#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// �R���X�g���N�^
Player::Player(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;

	pos  = { 0.0f, 0.0f };
	size = { 240.0f, 270.0f };

	Load("rsc/img/player.png", "pl");
	LoadInfo("rsc/info/player.info");

	updata = &Player::Wait;
}

// �f�X�g���N�^
Player::~Player()
{
}

// �L�[�̓���
bool Player::CheckKey(const int & i)
{
	return in.lock()->CheckKey(i);
}

// �g���K�[�̓���
bool Player::Triger(const int & i)
{
	return in.lock()->Triger(i);
}

// �ҋ@���̏���
void Player::Wait(void)
{
	if (st != "wait")
	{
		return;
	}

	if (CheckKey(INPUT_RIGHT))
	{
		reverse = false;
		SetState("walk");
		updata = &Player::Walk;
	}
	else if(CheckKey(INPUT_LEFT))
	{
		reverse = true;
		SetState("walk");
		updata = &Player::Walk;
	}
}

// �������̏���
void Player::Walk(void)
{
	if (st != "walk")
	{
		return;
	}

	if (CheckKey(INPUT_RIGHT))
	{
		reverse = false;
	}
	else if (CheckKey(INPUT_LEFT))
	{
		reverse = true;
	}
	else
	{
		SetState("wait");
		updata = &Player::Wait;
	}
}

// ����
void Player::UpData(void)
{
	Animator();

	(this->*updata)();
}

// �`��
void Player::Draw(void)
{
	DrawImg("pl", pos.x, pos.y, size.x, size.y);
}
