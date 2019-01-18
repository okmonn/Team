#pragma once
#include "Enemy.h"

class Enemy1 :
	public Enemy
{
public:
	// �R���X�g���N�^
	Enemy1(std::weak_ptr<Application>app, std::weak_ptr<Camera> cam, std::weak_ptr<Chara>pl, const Vec2f& pos = 0.0f, const Vec2f& size = 100.0f);
	// �f�X�g���N�^
	~Enemy1();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �X�e�[�^�X���̏����̃Z�b�g
	void SetFunc(void);

	// �ҋ@���̏���
	void Wait(void);


	// �֐��|�C���^
	std::unordered_map<std::string, std::function<void(Enemy1*)>>func;
};
