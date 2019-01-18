#include "Enemy1.h"
#include "../Application/Application.h"

// �R���X�g���N�^
Enemy1::Enemy1(std::weak_ptr<Application> app, std::weak_ptr<Camera> cam, std::weak_ptr<Chara> pl, const Vec2f & pos, const Vec2f & size)
{
	this->app	= app;
	this->pl	= pl;
	this->pos	= pos;
	this->size	= size;
	this->cam	= cam;

	LoadImg("1", "_rsc/img/Enemy1.png");
	LoadInfo("_rsc/info/player.info");
	SetFunc();
}

// �f�X�g���N�^
Enemy1::~Enemy1()
{
	Delete();
}

// �X�e�[�^�X���̏����̃Z�b�g
void Enemy1::SetFunc(void)
{
	func.clear();

	func["wait"] = &Enemy1::Wait;
	func["walk"] = &Enemy1::Walk;
	func["attack"] = &Enemy1::Attack;
	func["damage"] = &Enemy1::Damage;
	func["dead"] = &Enemy1::Dead;
}

// �ҋ@���̏���
void Enemy1::Wait(void)
{
	if (state != "wait")
	{
		return;
	}

	//�������ĕ������U�����邩����
}

void Enemy1::Walk(void)
{
	if (state != "walk")
	{
		return;
	}


}

void Enemy1::Attack(void)
{
	if (state != "attack")
	{
		return;
	}
}

void Enemy1::Damage(void)
{
	if (state != "damage")
	{
		return;
	}
}

void Enemy1::Dead(void)
{
	if (state != "dead")
	{
		return;
	}
}

// �`��
void Enemy1::Draw(void)
{
	DrawImg("1", pos, size);
}

// ����
void Enemy1::UpData(void)
{
	Animator();
	func[state](this);
}
