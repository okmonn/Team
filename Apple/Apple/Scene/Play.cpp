#include "Play.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// �R���X�g���N�^
Play::Play(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// �f�X�g���N�^
Play::~Play()
{
}

// ����
void Play::UpData(void)
{
}

// �`��
void Play::Draw(void)
{
	un.lock()->DrawBox(0, 0, 320, 480, 1, 0, 0);
}
