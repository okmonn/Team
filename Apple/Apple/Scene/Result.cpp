#include "Result.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// �R���X�g���N�^
Result::Result(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// �f�X�g���N�^
Result::~Result()
{
	Delete();
}

// ����
void Result::UpData(void)
{
}

// �`��
void Result::Draw(void)
{
}
