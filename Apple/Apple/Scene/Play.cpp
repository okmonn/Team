#include "Play.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Game/Game.h"
#include "Title.h"
#include "../Character/Player.h"
#include "../Camera/Camera.h"
#include "../Map/Map.h"

// �R���X�g���N�^
Play::Play(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
	map = std::make_shared<Map>();
	Camera::Get().Init();
	Create();
}

// �f�X�g���N�^
Play::~Play()
{
	Delete();
}

// �N���X�̃C���X�^���X
void Play::Create(void)
{
	pl = std::make_shared<Player>(in, un);
	Load("rsc/img/BG.png", "bg");
	Load("rsc/img/GR.png", "gr");
}

// ����
void Play::UpData(void)
{
	Camera::Get().UpData(pl->GetPos());
	pl->UpData();
	DrawImg("gr", 0.0f, 0.0f,
	640.0f, 480.0f, -Camera::Get().GetPos().x, 0.0f, 640.0f, 480.0f);

	DrawImg("bg", 0.0f, 0.0f,
		640.0f, 338.0f, -Camera::Get().GetPos().x, 640.0f, 480.0f, 640.0f, 338.0f);

	printf("%.0f:::%.1f\n", pl->GetPos().x, pl->GetPos().y);
}

// �`��
void Play::Draw(void)
{
	pl->Draw();
}
