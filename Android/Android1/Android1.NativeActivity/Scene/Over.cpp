#include "Over.h"
#include "../Game/Game.h"
#include "Title.h"
#include "../etc/Typedef.h"
#include "DxLib.h"

// 移動速度
const float speed = 10.0f;

// コンストラクタ
Over::Over()
{
	alpha = 0;
	draw = &Over::NormalDraw;
	updata = &Over::NormalUpData;

	Load();
}

// デストラクタ
Over::~Over()
{
}

// 読み込み
void Over::Load(void)
{
	AddImage("Over/overback.png", { 1080.0f, 1920.0f }, {0.0f, -1920.0f});
	AddImage("Over/over.png", { 605.0f,  194.0f }, {WINDOW_X / 2 - 605 / 2, WINDOW_Y / 2 - 194 / 2});
}

// 通常描画
void Over::NormalDraw(void)
{
	DrawGraph("overback");
}

// 移行描画
void Over::MoveDraw(void)
{
	DrawGraph("overback");
	DrawGraph("over");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

// 描画
void Over::Draw(void)
{
	(this->*draw)();
}

// 通常処理
void Over::NormalUpData(void)
{
	if (data["overback"].pos.y < 0)
	{
		data["overback"].pos.y += speed;
	}
	else
	{
		draw = &Over::MoveDraw;
		updata = &Over::MoveUpData;
	}
}

// 移行処理
void Over::MoveUpData(void)
{
	if (alpha < 255)
	{
		alpha += alphaSpeed / 2;
	}
	else
	{
		Game::Get().ChangeScene(new Title());
	}
}

// 処理
void Over::UpData(void)
{
	(this->*updata)();
}
