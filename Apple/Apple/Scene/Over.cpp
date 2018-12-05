#include "Over.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// コンストラクタ
Over::Over(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// デストラクタ
Over::~Over()
{
	Delete();
}

// 処理
void Over::UpData(void)
{
}

// 描画
void Over::Draw(void)
{
}
