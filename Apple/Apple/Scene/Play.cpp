#include "Play.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Character/Player.h"

// �R���X�g���N�^
Play::Play(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;

	Create();
}

// �f�X�g���N�^
Play::~Play()
{
}

// �N���X�̃C���X�^���X
void Play::Create(void)
{
	pl = std::make_shared<Player>(in, un);
}

// ����
void Play::UpData(void)
{
	pl->UpData();
}

// �`��
void Play::Draw(void)
{
	pl->Draw();
}
