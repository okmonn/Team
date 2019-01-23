#pragma once
#include "Enemy.h"

class Enemy2 :
	public Enemy 
{
public:
	// �R���X�g���N�^
	Enemy2(std::weak_ptr<Application>app, std::weak_ptr<Camera> cam, std::weak_ptr<Player>pl, const Vec2f& pos = 0.0f, const Vec2f& size = 100.0f);
	// �f�X�g���N�^
	~Enemy2();

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

	// �U�����̏���
	void Attack(void);

	// �_���[�W���̏���
	void Damage(void);

	// ���S���̏���
	void Dead(void);


	// �֐��|�C���^
	std::unordered_map<std::string, std::function<void(Enemy2*)>>func;
};