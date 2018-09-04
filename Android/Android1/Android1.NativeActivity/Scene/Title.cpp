#include "Title.h"
#include "Description.h"
#include "../Game/Game.h"
#include "../Touch/Touch.h"
#include "DxLib.h"

// 移動速度
const float speed = 4.0f;

// コンストラクタ
Title::Title() : 
	large(1.0f)
{
	update = &Title::NormalUpData;
	draw = &Title::NormalDraw;

	Load();
}

// デストラクタ
Title::~Title()
{
}

// 画像読み込み
void Title::Load(void)
{
	AddImage("Title/titleback.png", { 1080.0f, 1916.0f });
	AddImage("Title/titleLogo.png", { 1080.0f, 1920.0f });
	AddImage("Title/yazirusi.png",  { 122.0f,  154.0f }, { (WINDOW_X - 122.0f) / 2, (WINDOW_Y + (154.0f * 2.0f)) / 2 });
	AddImage("Title/setsumei.png",  { 960.0f, 320.0f },  { (WINDOW_X - 960.0f) / 2, (WINDOW_Y - 320.0f * 1.5f) });
	AddImage("Item/apple.png",      { 128.0f, 128.0f },  { 865.0f, 670.0f });
	AddImage("Item/greenapple.png", { 128.0f, 128.0f },  { 98.0f, 440.0f });
}

// 通常描画
void Title::NormalDraw(void)
{
	DrawModiGraph("titleback", { 1080.0f, 1920.0f });
	DrawRectRotaGraph("apple", { 0.0f, 0.0f }, data["apple"].size);
	DrawRectRotaGraph("greenapple", { 0.0f, 0.0f }, data["apple"].size);
	DrawGraph("titleLogo");
	DrawGraph("yazirusi");
	DrawGraph("setsumei");
}

// 移行描画
void Title::MoveDraw(void)
{
	DrawRectRotaGraph("titleback", { 0.0f, 0.0f }, {1080.0f, 1916.0f}, large);
}

// 描画
void Title::Draw(void)
{
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	(this->*draw)();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 通常処理
void Title::NormalUpData(void)
{
	if (Touch::Get().Flick() == true)
	{
		draw = &Title::MoveDraw;
		update = &Title::MoveUpData;
	}
	else
	{
		if (data["yazirusi"].pos.y > WINDOW_Y / 2)
		{
			data["yazirusi"].pos.y -= speed;
		}
		else
		{
			data["yazirusi"].pos.y = (WINDOW_Y + (154.0f * 2.0f)) / 2;
		}

		if (data["apple"].pos.x >= 865.0f)
		{
			if (data["apple"].pos.y >= 440.0f)
			{
				data["apple"].pos.y -= speed;
			}
			else
			{
				data["apple"].pos = { 98.0f, 440.0f };
			}
		}
		else
		{
			if (data["apple"].pos.y <= 670.0f)
			{
				data["apple"].pos.y += speed;
			}
			else
			{
				data["apple"].pos = { 865.0f, 670.0f };
			}
		}

		if (data["greenapple"].pos.x >= 865.0f)
		{
			if (data["greenapple"].pos.y >= 440.0f)
			{
				data["greenapple"].pos.y -= speed;
			}
			else
			{
				data["greenapple"].pos = { 98.0f, 440.0f };
			}
		}
		else
		{
			if (data["greenapple"].pos.y <= 670.0f)
			{
				data["greenapple"].pos.y += speed;
			}
			else
			{
				data["greenapple"].pos = { 865.0f, 670.0f };
			}
		}
	}
}

// 移行処理
void Title::MoveUpData(void)
{
	if (alpha > 0)
	{
		alpha -= alphaSpeed;
		large += 0.1f;
		data["titleback"].pos.x -= speed * 13.0f;
	}
	else
	{
		Game::Get().ChangeScene(new Description());
	}
}


// 処理
void Title::UpData(void)
{
	(this->*update)();
}
