#pragma once
#include "Character.h"

class Player :
	public Character
{
public:
	// �R���X�g���N�^
	Player(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Player();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:

};
