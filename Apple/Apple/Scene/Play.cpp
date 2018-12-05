#include "Play.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Game/Game.h"
#include "Title.h"
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
	{
		static int i = 0;
		pl->UpData();
		if (in.lock()->CheckKey(INPUT_UP))
		{
			i--;
		}
		if (in.lock()->CheckKey(INPUT_DOWN))
		{
			i++;
		}
		un.lock()->DrawBox(0, 0, i*2, 48,
			0.088, 0.5, 0.2, 1);
	}
	printf("%.0f\n", pl->GetPos().x);
}

// �`��
void Play::Draw(void)
{
	pl->Draw();
}
