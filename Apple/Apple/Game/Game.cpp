#include "Game.h"
#include "../Scene/Title.h"

std::shared_ptr<Scene> Game::scene = nullptr;

// �R���X�g���N�^
Game::Game(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	ChangeScene(new Title(in, un));
}

// �f�X�g���N�^
Game::~Game()
{
	scene.reset();
}

// �V�[���ڍs
void Game::ChangeScene(Scene * scene)
{
	Game::scene.reset(scene);
}

// ����
void Game::Run(void)
{
	scene->UpData();
	scene->Draw();
}
