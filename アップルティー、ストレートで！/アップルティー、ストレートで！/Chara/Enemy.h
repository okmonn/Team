#pragma once
#include "Chara.h"

class Enemy :
	public Chara
{
public:
	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	virtual ~Enemy();

protected:
	// �v���C���[
	std::weak_ptr<Chara>pl;
};
