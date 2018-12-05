#include "Game.h"
#include "../Scene/Title.h"

std::shared_ptr<Scene> Game::scene = nullptr;

// コンストラクタ
Game::Game(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	ChangeScene(new Title(in, un));
}

// デストラクタ
Game::~Game()
{
	scene.reset();
}

// シーン移行
void Game::ChangeScene(Scene * scene)
{
	Game::scene.reset(scene);
}

// 処理
void Game::Run(void)
{
	scene->UpData();
	scene->Draw();
}
