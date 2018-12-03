#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// コンストラクタ
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

// デストラクタ
Player::~Player()
{
}

// キーの入力
bool Player::CheckKey(const int & i)
{
	return in.lock()->CheckKey(i);
}

// トリガーの入力
bool Player::Triger(const int & i)
{
	return in.lock()->Triger(i);
}

// 待機時の処理
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

// 歩き時の処理
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

// 処理
void Player::UpData(void)
{
	Animator();

	(this->*updata)();
}

// 描画
void Player::Draw(void)
{
	DrawImg("pl", pos.x, pos.y, size.x, size.y);
}
