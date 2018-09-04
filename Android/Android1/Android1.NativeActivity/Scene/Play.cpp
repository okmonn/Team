#include "Play.h"
#include "../Game/Game.h"
#include "../etc/Typedef.h"
#include "Over.h"
#include "Clear.h"
#include "DxLib.h"

// コンストラクタ
Play::Play() : 
	fade(false), color(GetColor(255,255,255))
{
	updata = &Play::MoveUpData;
}

// デストラクタ
Play::~Play()
{
}

// 描画
void Play::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

// 通常処理
void Play::NormalUpData(void)
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		fade = true;
		color = GetColor(0, 0, 0);
		updata = &Play::MoveUpData;
	}
}

// 移行処理
void Play::MoveUpData(void)
{
	alpha += (fade == false) ? -alphaSpeed : alphaSpeed;
	if (fade == false)
	{
		if (alpha <= 0)
		{
			alpha = 0;
			updata = &Play::NormalUpData;
		}
	}
	else
	{
		if (alpha >= 255)
		{
			Game::Get().ChangeScene(new Over());
		}
	}
}

// 処理
void Play::UpData(void)
{
	(this->*updata)();
}
