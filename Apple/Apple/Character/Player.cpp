#include "Player.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// コンストラクタ
Player::Player(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// デストラクタ
Player::~Player()
{
}

// 処理
void Player::UpData(void)
{
}

// 描画
void Player::Draw(void)
{
}
