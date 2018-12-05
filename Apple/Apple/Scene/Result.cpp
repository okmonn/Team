#include "Result.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// コンストラクタ
Result::Result(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// デストラクタ
Result::~Result()
{
	Delete();
}

// 処理
void Result::UpData(void)
{
}

// 描画
void Result::Draw(void)
{
}
