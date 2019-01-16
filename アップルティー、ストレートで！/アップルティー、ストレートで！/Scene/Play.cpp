#include "Play.h"
#include "../Chara/Player.h"
#include "../Chara/EnemyMane.h"
#include "../Application/Application.h"

// �R���X�g���N�^
Play::Play(std::weak_ptr<Application> app)
{
	this->app = app;

	Create();
}

// �f�X�g���N�^
Play::~Play()
{
}

// ����
void Play::Create(void)
{
	pl = std::make_shared<Player>(app, 400.0f, 100.0f);
	enemy = std::make_shared<EnemyMane>(app, pl);
	enemy->Create("1", 100.0f, 100.0f);
	enemy->Create("1", 200.0f, 100.0f);
}

// �`��
void Play::Draw(void)
{
	pl->Draw();
	enemy->Draw();
}

// ����
void Play::UpData(void)
{
	pl->UpData();
	enemy->UpData();
}
