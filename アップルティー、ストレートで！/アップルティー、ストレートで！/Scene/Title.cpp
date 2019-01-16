#include "Title.h"
#include "../Input/Input.h"
#include "../GameMane/GameMane.h"
#include "../Application/Application.h"
#include "Play.h"

// �R���X�g���N�^
Title::Title(std::weak_ptr<Application> app)
{
	this->app = app;
}

// �f�X�g���N�^
Title::~Title()
{
}

// �`��
void Title::Draw(void)
{
}

// ����
void Title::UpData(void)
{
	if (Input::Get().Triger(INPUT_RETURN))
	{
		GameMane::Get().ChangeScene(new Play(app));
	}
}
