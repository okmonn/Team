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

	SetFunc();
}

// �f�X�g���N�^
Player::~Player()
{
}

// �X�e�[�^�X���̏����̃Z�b�g
void Player::SetFunc(void)
{
	func.clear();

	func["wait"]    = &Player::Wait;
	func["walk"]    = &Player::Walk;
	func["avoid"]   = &Player::Avoid;
	func["attack1"] = &Player::Attack1;
	func["attack2"] = &Player::Attack2;
	func["sliding"] = &Player::Sliding;
	func["damage"]  = &Player::Damage;
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

	//�X�e�[�^�X���ړ��ɍX�V
	if (CheckKey(INPUT_RIGHT))
	{
		reverse = false;
		SetState("walk");
	}
	else if(CheckKey(INPUT_LEFT))
	{
		reverse = true;
		SetState("walk");
	}
	//�X�e�[�^�X���U��1�ɍX�V
	else if (CheckKey(INPUT_Z))
	{
		SetState("attack1");
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
		pos.x += speed;
	}
	else if (CheckKey(INPUT_LEFT))
	{
		reverse = true;
		pos.x -= speed;
	}
	//�X�e�[�^�X��ҋ@�ɍX�V
	else
	{
		SetState("wait");
	}
}

// ������̏���
void Player::Avoid(void)
{
	if (st != "avoid")
	{
		return;
	}
}

// �U��1���̏���
void Player::Attack1(void)
{
	if (st != "attack1")
	{
		return;
	}

	if (CheckAnimEnd())
	{
		//�X�e�[�^�X���U��2�ɍX�V
		if (CheckKey(INPUT_Z))
		{
			SetState("attack2");
			return;
		}

		//�X�e�[�^�X��ҋ@�ɍX�V
		SetState("wait");
	}
}

// �U��2���̏���
void Player::Attack2(void)
{
	if (st != "attack2")
	{
		return;
	}

	//�X�e�[�^�X��ҋ@�ɍX�V
	if (CheckAnimEnd())
	{
		SetState("wait");
	}
}

// �X���C�f�B���O���̏���
void Player::Sliding(void)
{
	if (st != "sliding")
	{
		return;
	}
}

// �_���[�W���̏���
void Player::Damage(void)
{
	if (st != "damage")
	{
		return;
	}
}

// ����
void Player::UpData(void)
{
	Animator();

	func[st](this);
}

// �`��
void Player::Draw(void)
{
	DrawImg("pl", pos.x, pos.y, size.x, size.y);
}
