#include "Description.h"
#include "Play.h"
#include "../Game/Game.h"
#include "../Touch/Touch.h"
#include "../etc/Typedef.h"
#include "DxLib.h"

// インデックステーブルの最大数
#define INDEX_MAX 4

// インデックステーブル
const std::string name[INDEX_MAX] = {
	"sousa1",
	"sousa2",
	"sousa3",
	"sousa4",
};

// コンストラクタ
Description::Description() : 
	index(0)
{
	func = &Description::NormalUpData;

	Load();
}

// デストラクタ
Description::~Description()
{
}

// 読み込み
void Description::Load(void)
{
	AddImage("Sousa/sousa1.png", { 1080.0f, 1920.0f });
	AddImage("Sousa/sousa2.png", { 1080.0f, 1920.0f });
	AddImage("Sousa/sousa3.png", { 1080.0f, 1920.0f });
	AddImage("Sousa/sousa4.png", { 1080.0f, 1920.0f });
}

// 描画
void Description::Draw(void)
{
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(name[index]);
	if (index != 0)
	{
		DrawTriangle(50, WINDOW_Y / 2 - 50 / 2, 0, WINDOW_Y / 2, 50, WINDOW_Y / 2 + 50 / 2, GetColor(0, 0, 0), true);
	}
	if (index != INDEX_MAX - 1)
	{
		DrawTriangle(WINDOW_X - 50, WINDOW_Y / 2 - 50 / 2, WINDOW_X, WINDOW_Y / 2, WINDOW_X - 50, WINDOW_Y / 2 + 50 / 2, GetColor(0, 0, 0), true);
	}
	DrawFormatString(WINDOW_X / 2 - 50, WINDOW_Y - 40 * 3, GetColor(255, 255, 255), "%d / %d", index + 1, INDEX_MAX);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

// 通常処理
void Description::NormalUpData(void)
{
	if (Touch::Get().Flick() == true)
	{
		if (Touch::Get().GetDir() == DIR::left)
		{
			if (index != INDEX_MAX - 1)
			{
				index = (index + 1 >= INDEX_MAX) ? index : ++index;
			}
			else
			{
				func = &Description::MoveUpData;
			}
		}
		else if (Touch::Get().GetDir() == DIR::right)
		{
			index = (index - 1 < 0) ? index : --index;
		}
	}
	else if (Touch::Get().Tap() == true)
	{
		if (Touch::Get().GetOldPos().x < WINDOW_X / 4)
		{
			index = (index - 1 < 0) ? index : --index;
		}
		else if(Touch::Get().GetOldPos().x > WINDOW_X - (WINDOW_X / 4))
		{
			if (index == INDEX_MAX - 1)
			{
				func = &Description::MoveUpData;
			}
			else
			{
				index = (index + 1 >= INDEX_MAX) ? 0 : ++index;
			}
		}
	}
}

// 移行処理
void Description::MoveUpData(void)
{
	if (alpha > 0)
	{
		alpha -= alphaSpeed;
	}
	else
	{
		Game::Get().ChangeScene(new Play());
	}
}

// 処理
void Description::UpData(void)
{
	(this->*func)();
}
