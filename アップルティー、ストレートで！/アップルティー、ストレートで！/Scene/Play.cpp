#include "Play.h"
#include "../Camera/Camera.h"
#include "../BackGround/BackGround.h"
#include "../Map/Map.h"
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
	cam   = std::make_shared<Camera>(app);
	back  = std::make_shared<BackGround>(app, cam);
	map   = std::make_shared<Map>(app);
	pl    = std::make_shared<Player>(app, cam, 400.0f, 100.0f);
	enemy = std::make_shared<EnemyMane>(app,cam, pl);
	//enemy->Create("2", 300.0f, 100.0f);

	cam->SetTarget(pl);
}

// �`��
void Play::Draw(void)
{
	back->Draw();
	pl->Draw();
	enemy->Draw();
}

// ����
void Play::UpData(void)
{
	cam->UpData();
	back->UpData();
	pl->UpData();
	enemy->UpData();

	auto read1 = map->GetRead();
	auto data  = map->GetData(pl->GetPos() + map->GetSize().x);
	auto read2 = map->GetRead();
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		float x = (map->GetSize().x * read1) + (map->GetSize().x * i / map->GetMass().x);
		float y = app.lock()->GetWinSize().y - i % map->GetMass().y * map->GetSize().y;
		switch (data[i])
		{
		case 1:
			enemy->Create("1", { x, y }, 100.0f);
			break;
		case 0:
		default:
			break;
		}
	}
}
