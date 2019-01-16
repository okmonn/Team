#include "Player.h"
#include "../Application/Application.h"

// コンストラクタ
Player::Player(std::weak_ptr<Application>app)
{
	this->app = app;
}

// デストラクタ
Player::~Player()
{
	Delete();
}

// 描画
void Player::Draw(void)
{
}

// 処理
void Player::UpData(void)
{
}
