#include "Player.h"

// コンストラクタ
Player::Player()
{
}

// デストラクタ
Player::~Player()
{
}

// 読み込み
void Player::Load(void)
{
	AddImage("Player/Nwait.png", { 240.0f, 270.0f }, { 4.0f, 4.0f }, 5);
}


// 描画
void Player::Draw(void)
{
}

// 処理
void Player::UpData(void)
{
}
