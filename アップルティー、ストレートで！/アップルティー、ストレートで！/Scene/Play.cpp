#include "Play.h"
#include "../Chara/Player.h"
#include "../Chara/EnemyMane.h"
#include "../Application/Application.h"
#include "../Camera/Camera.h"
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
	cam = std::make_shared<Camera>(app);
	pl = std::make_shared<Player>(app, 400.0f, 100.0f,cam);
	enemy = std::make_shared<EnemyMane>(app,cam, pl);
	enemy->Create("1", 100.0f, 100.0f);
	enemy->Create("1", 200.0f, 100.0f);

}

// 描画
void Play::Draw(void)
{
	pl->Draw();
	enemy->Draw();
}

// 処理
void Play::UpData(void)
{
	pl->UpData();
	enemy->UpData();
}
