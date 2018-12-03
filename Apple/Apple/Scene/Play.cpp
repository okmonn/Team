#include "Play.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Character/Player.h"

// コンストラクタ
Play::Play(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;

	Create();
}

// デストラクタ
Play::~Play()
{
}

// クラスのインスタンス
void Play::Create(void)
{
	pl = std::make_shared<Player>(in, un);
}

// 処理
void Play::UpData(void)
{
	pl->UpData();
}

// 描画
void Play::Draw(void)
{
	pl->Draw();
}
