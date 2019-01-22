#pragma once
#include "Chara.h"

class Player;

class Enemy :
	public Chara
{
public:
	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	virtual ~Enemy();

protected:
	// ���[�J�����W�̍X�V
	void UpDataLocal(void);

	// �����_���ȃ^�[�Q�b�g���W�̐���
	Vec2f GetRandomPos(const Vec2f& range);

	// �����蔻��
	bool CheckHit(void);


	// �v���C���[
	std::weak_ptr<Player>pl;

	// �^�[�Q�b�g���W
	Vec2f target;
};
