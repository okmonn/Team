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

	LoadImg("1", "_rsc/img/player.png");
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
}

// �ҋ@���̏���
void Enemy1::Wait(void)
{
	if (state != "wait")
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
