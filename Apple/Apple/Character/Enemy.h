#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	// �R���X�g���N�^
	Enemy(Map map);
	// �f�X�g���N�^
	virtual ~Enemy();

protected:
	// �ҋ@���̏���
	void Wait(void);

	// �ړ����̏���
	void Walk(void);

	// �U�����̏���
	void Attack(void);

	// �_���[�W���̏���
	void Damage(void);
};