#include "Play.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// コンストラクタ
Play::Play(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// デストラクタ
Play::~Play()
{
}

// 処理
void Play::UpData(void)
{
}

// 描画
void Play::Draw(void)
{
	un.lock()->DrawBox(0, 0, 320, 480, 1, 0, 0);
}
