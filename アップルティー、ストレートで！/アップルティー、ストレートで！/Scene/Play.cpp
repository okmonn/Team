#include "Play.h"
#include "../Camera/Camera.h"
#include "../BackGround/BackGround.h"
#include "../Chara/Player.h"
#include "../Chara/EnemyMane.h"
#include "../Application/Application.h"

// コンストラクタ
Play::Play(std::weak_ptr<Application> app)
{
	this->app = app;

	Create();
}

// デストラクタ
Play::~Play()
{
}

// 生成
void Play::Create(void)
{
	cam   = std::make_shared<Camera>(app);
	back  = std::make_shared<BackGround>(app, cam);
	pl    = std::make_shared<Player>(app, cam, 400.0f, 100.0f);
	enemy = std::make_shared<EnemyMane>(app,cam, pl);
	enemy->Create("1", 100.0f, 100.0f);
	//enemy->Create("2", 300.0f, 100.0f);

	cam->SetTarget(pl);
}

// 描画
void Play::Draw(void)
{
	back->Draw();
	pl->Draw();
	enemy->Draw();
}

// 処理
void Play::UpData(void)
{
	cam->UpData();
	back->UpData();
	pl->UpData();
	enemy->UpData();
}
