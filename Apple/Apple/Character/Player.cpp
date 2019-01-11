#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Camera/Camera.h"
#include "../Game/Game.h"
#include "../Map/Map.h"
#define GROUND_Y (74.0f)
// �R���X�g���N�^
Player::Player(std::weak_ptr<Input> in, std::weak_ptr<Union> un, std::weak_ptr<Map>map)
{
	this->in = in;
	this->un = un;
	this->map = map;
	pos  = { 0.0f, this->map.lock()->GetGroundPos().y };
	size = { 240.0f, 270.0f };
	Load("rsc/img/player.png", "pl");
	LoadInfo("rsc/info/player.info");

	SetFunc();
}

// �f�X�g���N�^
Player::~Player()
{
	Delete();
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

	if (CheckKey(INPUT_UP))
	{
		SetState("walk");
	}
	else if (CheckKey(INPUT_DOWN))
	{
		SetState("walk");
	}

	//�X�e�[�^�X���ړ��ɍX�V
	if (CheckKey(INPUT_RIGHT))
	{
		reverse = false;
		SetState("walk");
	}
	else if (CheckKey(INPUT_LEFT))
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

	// �ړ��͈͊O����

	if (CheckKey(INPUT_UP))
	{
		//Game::Run();
		if ((pos.y - speed) < map.lock()->GetGroundPos().y)
		{
			pos.y -= 0.0f;
		}
		else
		{
			pos.y -= speed;
		}
	}
	else if (CheckKey(INPUT_DOWN))
	{
		pos.y += speed;
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
	if ( st != "avoid" )
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

	lpos = { pos + Camera::Get().GetPos() };

}

// �`��
void Player::Draw(void)
{
	

	DrawImg("pl", lpos.x, lpos.y - size.y, size.x, size.y);

	//DrawImg("pl", pos.x + Camera::Get().GetPos().x, pos.y + Camera::Get().GetPos().y + GROUND_Y, size.x, size.y);
}
