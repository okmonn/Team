#include "GameMane.h"
#include "../Input/Input.h"
#include "../Application/Application.h"
#include "../Scene/Title.h"
#include "../Typedef.h"

const Vec2 winSize = { WindowSize.x,WindowSize.y };

// �R���X�g���N�^
GameMane::GameMane()
{
}

// �f�X�g���N�^
GameMane::~GameMane()
{
}

// �V�[���̈ڍs
void GameMane::ChangeScene(Scene * scene)
{
	this->scene.reset(scene);
}

// ������
void GameMane::Init(void)
{
	app = std::make_shared<Application>(winSize);
	ChangeScene(new Title(app));
}

// �`��
void GameMane::Draw(void)
{
	scene->Draw();
}

// ����
void GameMane::UpData(void)
{
	scene->UpData();
}

// ����
void GameMane::Run(void)
{
	Init();
	while (app->CheckMsg() && Input::Get().InputKey(INPUT_ESCAPE) == false)
	{
		app->Clear();
		Draw();
		UpData();
		app->Execution();
	}
	End();
}

// �I��
void GameMane::End(void)
{
	scene.reset();
	app.reset();
}
