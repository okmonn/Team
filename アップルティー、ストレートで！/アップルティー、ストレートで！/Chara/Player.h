#pragma once
#include "Chara.h"

class Player :
	public Chara
{
public:
	// �R���X�g���N�^
	Player(std::weak_ptr<Application>app);
	// �f�X�g���N�^
	~Player();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:

};
