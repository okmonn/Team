#include "Player.h"
#include "../Input/Input.h"
#include "../Application/Application.h"
#include "../Camera/Camera.h"
// コンストラクタ
Player::Player(std::weak_ptr<Application>app, const Vec2f & pos, const Vec2f & size,std::shared_ptr<Camera> cam)
{
	this->app  = app;
	this->pos  = pos;
	this->size = size;
	this->cam = cam;
	LoadImg("pl", "_rsc/img/player.png");
	LoadInfo("_rsc/info/player.info");
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

// 待機時の処理
void Player::Wait(void)
{
	if (state != "wait")
	{
		return;
	}

	if (Input::Get().InputKey(INPUT_RIGHT))
	{
		reverse = false;
		SetState("walk");
	}
	else if (Input::Get().InputKey(INPUT_LEFT))
	{
		reverse = true;
		SetState("walk");
	}
	else if (Input::Get().InputKey(INPUT_UP) | Input::Get().InputKey(INPUT_DOWN))
	{
		SetState("walk");
	}
	else
	{
	}
}

// 歩行時の処理
void Player::Walk(void)
{
	if (state != "walk")
	{
		return;
	}

	if (Input::Get().InputKey(INPUT_RIGHT))
	{
		reverse = false;
		pos.x += speed;
	}
	else if (Input::Get().InputKey(INPUT_LEFT))
	{
		reverse = true;
		pos.x -= speed;
	}
	else if (Input::Get().InputKey(INPUT_UP))
	{
		pos.y -= speed;
	}
	else if (Input::Get().InputKey(INPUT_DOWN))
	{
		pos.y += speed;
	}
	else
	{
		SetState("wait");
	}
}

// 回避時の処理
void Player::Avoid(void)
{
	if (state != "avoid")
	{
		return;
	}
}

// 攻撃1時の処理
void Player::Attack1(void)
{
	if (state != "attack1")
	{
		return;
	}
}

// 攻撃2時の処理
void Player::Attack2(void)
{
	if (state != "attack2")
	{
		return;
	}
}

// スライディング時の処理
void Player::Sliding(void)
{
	if (state != "sliding")
	{
		return;
	}
}

// ダメージ時の処理
void Player::Damage(void)
{
	if (state != "damage")
	{
		return;
	}
}

// 描画
void Player::Draw(void)
{
	cam.lock()->UpData(GetPos());
	DrawImg("pl", pos, size);
}

// 処理
void Player::UpData(void)
{
	Animator();
	func[state](this);
}
