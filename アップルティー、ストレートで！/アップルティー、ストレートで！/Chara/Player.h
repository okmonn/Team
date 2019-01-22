#pragma once
#include "Chara.h"

class Player :
	public Chara
{
public:
	// �R���X�g���N�^
	Player(std::weak_ptr<Application> app, std::weak_ptr<Camera>cam, const Vec2f & pos, const Vec2f & size);
	// �f�X�g���N�^
	~Player();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �X�e�[�^�X���̏����̃Z�b�g
	void SetFunc(void);

	// �ҋ@���̏���
	void Wait(void);

	// ���s���̏���
	void Walk(void);

	// ������̏���
	void Avoid(void);

	// �U��1���̏���
	void Attack1(void);

	// �U��2���̏���
	void Attack2(void);

	// �X���C�f�B���O���̏���
	void Sliding(void);

	// �_���[�W���̏���
	void Damage(void);


	// �֐��|�C���^
	std::unordered_map<std::string, std::function<void(Player*)>>func;
};
