#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Camera/Camera.h"
#include "../Game/Game.h"
#include "../Map/Map.h"
#define GROUND_Y (74.0f)
// コンストラクタ
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

	if (CheckKey(INPUT_UP))
	{
		SetState("walk");
	}
	else if (CheckKey(INPUT_DOWN))
	{
		SetState("walk");
	}

	//ステータスを移動に更新
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

	// 移動範囲外判定

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
	//ステータスを待機に更新
	else
	{
		SetState("wait");
	}
}

// 回避時の処理
void Player::Avoid(void)
{
	if ( st != "avoid" )
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

	lpos = { pos + Camera::Get().GetPos() };

}

// 描画
void Player::Draw(void)
{
	

	DrawImg("pl", lpos.x, lpos.y - size.y, size.x, size.y);

	//DrawImg("pl", pos.x + Camera::Get().GetPos().x, pos.y + Camera::Get().GetPos().y + GROUND_Y, size.x, size.y);
}
