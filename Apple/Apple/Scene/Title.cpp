#include "Title.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Game/Game.h"
#include "Play.h"

// �R���X�g���N�^
Title::Title(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;
}

// �f�X�g���N�^
Title::~Title()
{
}

// ����
void Title::UpData(void)
{
	if (in.lock()->Triger(INPUT_RETURN))
	{
		Game::ChangeScene(new Play(in, un));
	}
}

// �`��
void Title::Draw(void)
{
	un.lock()->DrawBox(0, 0, 640, 240, 1, 0, 0);
}
