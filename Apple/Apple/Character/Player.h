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
	// �L�[�̓���
	bool CheckKey(const int& i);

	// �g���K�[�̓���
	bool Triger(const int& i);

	// �ҋ@���̏���
	void Wait(void);

	// �������̏���
	void Walk(void);


	// �֐��|�C���^
	void(Player::*updata)(void);
};
