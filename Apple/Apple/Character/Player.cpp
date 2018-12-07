#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Camera/Camera.h"

// コンストラクタ
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

// デストラクタ
Player::~Player()
{
	Delete();
}

// ステータス毎の処理のセット
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

	//ステータスを移動に更新
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
	//ステータスを攻撃1に更新
	else if (CheckKey(INPUT_Z))
	{
		SetState("attack1");
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
		pos.x += speed;
	}
	else if (CheckKey(INPUT_LEFT))
	{
		reverse = true;
		pos.x -= speed;
	}
	//ステータスを待機に更新
	else
	{
		SetState("wait");
	}
}

// 回避時の処理
void Player::Avoid(void)
{
	if (st != "avoid")
	{
		return;
	}
}

// 攻撃1時の処理
void Player::Attack1(void)
{
	if (st != "attack1")
	{
		return;
	}

	if (CheckAnimEnd())
	{
		//ステータスを攻撃2に更新
		if (CheckKey(INPUT_Z))
		{
			SetState("attack2");
			return;
		}

		//ステータスを待機に更新
		SetState("wait");
	}
}

// 攻撃2時の処理
void Player::Attack2(void)
{
	if (st != "attack2")
	{
		return;
	}

	//ステータスを待機に更新
	if (CheckAnimEnd())
	{
		SetState("wait");
	}
}

// スライディング時の処理
void Player::Sliding(void)
{
	if (st != "sliding")
	{
		return;
	}
}

// ダメージ時の処理
void Player::Damage(void)
{
	if (st != "damage")
	{
		return;
	}
}

// 処理
void Player::UpData(void)
{
	Animator();

	func[st](this);
}

// 描画
void Player::Draw(void)
{
	DrawImg("pl", pos.x + Camera::Get().GetPos().x, pos.y + Camera::Get().GetPos().y, size.x, size.y);
}
