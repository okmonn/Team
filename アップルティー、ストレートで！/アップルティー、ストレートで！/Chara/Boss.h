#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	//�R���X�g���N�^
	Boss(std::weak_ptr<Application>app, std::weak_ptr<Camera> cam, std::weak_ptr<Player>pl,const Vec2f& pos = 0.0f, const Vec2f& size = 100.0f);
	//�f�X�g���N�^
	~Boss();

	//�`��
	void Draw(void);
	//����
	void UpData(void);

private:
	//�X�e�[�^�X���̏����̃Z�b�g
	void SetFunc(void);

	//�ҋ@���̏���
	void Wait(void);

	//���s���̏���
	void Walk(void);

	//���݂��U�����̏���
	void Attack1(void);

	//���U�����̏���
	void Attack2(void);

	//�˂��U�����̏���
	void Attack3(void);

	//�_���[�W���̏���
	void Damage(void);

	//��_���[�W�̏���
	void BigDamage(void);

	//���S���̏���
	void Dead(void);

	//�֐��|�C���^
	std::unordered_map<std::string, std::function<void(Boss*)>>func;
};

