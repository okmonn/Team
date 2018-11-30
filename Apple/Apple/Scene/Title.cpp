#include "Title.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Game/Game.h"
#include "Play.h"

// コンストラクタ
Title::Title(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// デストラクタ
Title::~Title()
{
}

// 処理
void Title::UpData(void)
{
	if (in.lock()->Triger(INPUT_RETURN))
	{
		Game::ChangeScene(new Play(in, un));
	}
}

// 描画
void Title::Draw(void)
{
	un.lock()->DrawBox(0, 0, 640, 240, 1, 0, 0);
}
