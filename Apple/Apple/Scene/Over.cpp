#include "Over.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// �R���X�g���N�^
Over::Over(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// �f�X�g���N�^
Over::~Over()
{
	Delete();
}

// ����
void Over::UpData(void)
{
}

// �`��
void Over::Draw(void)
{
}
