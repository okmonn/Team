#include "Play.h"
#include "../Chara/Player.h"
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
	pl = std::make_shared<Player>(app);
}

// �`��
void Play::Draw(void)
{
}

// ����
void Play::UpData(void)
{
}
