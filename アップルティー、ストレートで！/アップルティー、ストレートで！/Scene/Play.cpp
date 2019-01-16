#include "Play.h"
#include "../Chara/Player.h"
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
	pl = std::make_shared<Player>(app);
}

// 描画
void Play::Draw(void)
{
}

// 処理
void Play::UpData(void)
{
}
