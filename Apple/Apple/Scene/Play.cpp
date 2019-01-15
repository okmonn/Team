#include "Play.h"
#include "Title.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Game/Game.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#include "../Character/Enemy1.h"
#include "../Camera/Camera.h"
#include "../Map/Map.h"
#include "../etc/Typedef.h"

// コンストラクタ
Play::Play(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	
	fadeflg.clear();
	fadeflg["start"] = true;
	this->in = in;
	this->un = un;
	map = std::make_shared<Map>();
	Camera::Get().Init();
	Create();
}

// デストラクタ
Play::~Play()
{
	Delete();
}

// クラスのインスタンス
void Play::Create(void)
{
	pl = std::make_shared<Player>(in, un, map);
	// en.push_back(std::make_shared<Enemy>(map));
	en = std::make_shared<Enemy1>(un,map);
	Load("rsc/img/BG.png", "bg");
	Load("rsc/img/GR.png", "gr");
}

// 処理
void Play::UpData(void)
{

	Camera::Get().UpData(pl->GetPos());
	pl->UpData();
	DrawImg("gr", 0.0f, 0.0f,
	WINDOW_SIZE_X, WINDOW_SIZE_Y, -Camera::Get().GetPos().x, 0.0f, 640.0f, 480.0f);

	DrawImg("bg", 0.0f, 0.0f,
		WINDOW_SIZE_X, WINDOW_SIZE_Y-200, -Camera::Get().GetPos().x, 640.0f, 480.0f, 640.0f, 338.0f);

	printf("%.0f:::%.1f\n", pl->GetPos().x, pl->GetPos().y);

	if (in.lock()->Triger(INPUT_RETURN))
	{
		fadeflg["end"] = true;
	}


}

// 描画
void Play::Draw(void)
{
	pl->Draw();
	en->Draw();
	/*
	for (auto itr : en)
	{
		itr->Draw();
	}
	*/
	if (fadeflg["start"] == true)
	{
		if (Screen_FadeIn(0.12, 0x000000))
		{
			fadeflg["start"] = false;
		};
	}
	if (fadeflg["end"] == true)
	{
		if (Screen_FadeOut(0.12, 0xffffff))
		{
			fadeflg["end"] = false;
		};
	}
}
