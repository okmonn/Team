#include "Player.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Application/Application.h"

// �R���X�g���N�^
Player::Player(std::weak_ptr<Application>app, std::weak_ptr<Camera>cam, const Vec2f & pos, const Vec2f & size)
{
	this->app  = app;
	this->cam  = cam;
	this->pos  = pos;
	this->lpos = pos;
	this->size = size;

	hp = 10;
	
	LoadImg("pl", "_rsc/img/player.png");
	LoadInfo("_rsc/info/player.info");
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

// �ҋ@���̏���
void Player::Wait(void)
{
	if (state != "wait")
	{
		return;
	}

	if (Input::Get().InputKey(INPUT_Z))
	{
		SetState("attack1");
	}

	if (Input::Get().InputKey(INPUT_LEFT))
	{
		reverse = true;
		SetState("walk");
	}

	else if (Input::Get().InputKey(INPUT_RIGHT))
	{
		reverse = false;
		SetState("walk");
	}

	if (Input::Get().InputKey(INPUT_UP) | Input::Get().InputKey(INPUT_DOWN))
	{
		SetState("walk");
	}
	else
	{
	}
}

// ���s���̏���
void Player::Walk(void)
{
	if (state != "walk")
	{
		return;
	}

	bool walking = false;

	if (Input::Get().InputKey(INPUT_RIGHT))
	{
		reverse = false;
		pos.x += speed;
		walking = true;
	}
	 if (Input::Get().InputKey(INPUT_LEFT))
	{
		reverse = true;
		pos.x -= speed;
		walking = true;
	}
	 if (Input::Get().InputKey(INPUT_UP))
	{
		pos.y -= speed;
		walking = true;
	}
	 if (Input::Get().InputKey(INPUT_DOWN))
	{
		pos.y += speed;
		walking = true;
	}

	 if (Input::Get().Triger(INPUT_X))
	 {
		 SetState("sliding");
	 }

	if(!walking)
	{
		SetState("wait");
	}
}

// ������̏���
void Player::Avoid(void)
{
	if (state != "avoid")
	{
		return;
	}
}

// �U��2���̏���
void Player::Attack1(void)
{
	// �ǌ����s����
	static bool atk_flg = false;
	if (state != "attack1")
	{
		return;
	}
	if (Input::Get().Triger(INPUT_Z))
	{
		atk_flg = true;
	}
	if (CheckAnimEnd())
	{
		SetState((atk_flg == true ? "attack2" : "wait"));
		atk_flg = false;
	}
}

// �U��2���̏���
void Player::Attack2(void)
{
	if (state != "attack2")
	{
		return;
	}
	if (CheckAnimEnd())
	{
		SetState("wait");
	}

}

// �X���C�f�B���O���̏���
void Player::Sliding(void)
{
	if (state != "sliding")
	{
		return;
	}

	if (!reverse)
	{
		pos.x += speed * 2.4;
	}
	else
	{
		pos.x -= speed * 2.4;
	}

	if (CheckAnimEnd())
	{
		SetState("wait");
	}

}
// �_���[�W���̏���
void Player::Damage(void)
{
	if (state != "damage")
	{
		return;
	}
}

// �`��
void Player::Draw(void)
{
	DrawImg("pl");

#if _DEBUG
	DrawRect();
#endif
}

// ����
void Player::UpData(void)
{
	UpDataLocal();
	Animator();
	func[state](this);
}
