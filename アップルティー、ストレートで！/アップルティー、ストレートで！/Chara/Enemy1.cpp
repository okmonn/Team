#include "Enemy1.h"
#include "../Camera/Camera.h"
#include "Player.h"
#include "../Application/Application.h"

// �ڍs�I�t�Z�b�g
#define OFFSET 1.0f

// �R���X�g���N�^
Enemy1::Enemy1(std::weak_ptr<Application> app, std::weak_ptr<Camera> cam, std::weak_ptr<Player> pl, const Vec2f & pos, const Vec2f & size)
{
	this->app  = app;
	this->cam  = cam;
	this->pl   = pl;
	this->pos  = pos;
	this->lpos = pos;
	this->size = size;

	hp = 3;

	LoadImg("1", "_rsc/img/Enemy1.png");
	LoadInfo("_rsc/info/enemy1.info");
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

	func["wait"]   = &Enemy1::Wait;
	func["walk"]   = &Enemy1::Walk;
	func["attack"] = &Enemy1::Attack;
	func["damage"] = &Enemy1::Damage;
	func["dead"]   = &Enemy1::Dead;
}

// �ҋ@���̏���
void Enemy1::Wait(void)
{
	if (state != "wait")
	{
		return;
	}

	//�v���C���[�Ƃ̋���
	Vec2f tmp = pl.lock()->GetCenter() - GetCenter();
	float distance = std::hypot(tmp.x, tmp.y);

	if (distance <= size.x / 2.0f)
	{
		SetState("attack");
	}
	else
	{
		if (!CheckAnimEnd())
		{
			return;
		}
		target = pl.lock()->GetCenter();
		SetState("walk");
	}
}

// �ړ����̏���
void Enemy1::Walk(void)
{
	if (state != "walk")
	{
		return;
	}

	if (target.x > GetCenter().x)
	{
		pos.x += speed;
	}
	else if(target.x < GetCenter().x)
	{
		pos.x -= speed;
	}

	if (target.y > GetCenter().y)
	{
		pos.y += speed;
	}
	else if(target.y < GetCenter().y)
	{
		pos.y -= speed;
	}

	Vec2f tmp = target - GetCenter();
	float distance = std::hypot(tmp.x, tmp.y);
	if (distance <= OFFSET)
	{
		SetState("wait");
	}
}

// �U�����̏���
void Enemy1::Attack(void)
{
	if (state != "attack")
	{
		return;
	}

	if (CheckAnimEnd())
	{
		SetState("wait");
	}
}

// �_���[�W���̏���
void Enemy1::Damage(void)
{
	if (state != "damage")
	{
		return;
	}

	if (hp <= 0)
	{
		SetState("dead");
		return;
	}

	if (CheckAnimEnd())
	{
		SetState("wait");
	}
}

// ���S���̏���
void Enemy1::Dead(void)
{
	if (state != "dead")
	{
		return;
	}

	if (CheckAnimEnd())
	{
		dead = true;
	}
}

// �`��
void Enemy1::Draw(void)
{
	DrawImg("1");

	for (auto& i : pl.lock()->GetRect())
	{
		app.lock()->DrawBox(i.rect.pos, i.rect.size, { 1.0f, 0.0f, 0.0f, 0.5f });
	}
	for (auto& i : GetRect())
	{
		app.lock()->DrawBox(i.rect.pos, i.rect.size, { 1.0f, 0.0f, 0.0f, 0.5f });
	}
}

// ����
void Enemy1::UpData(void)
{
	UpDataLocal();
	Animator();
	if (CheckHit())
	{
		SetState("damage");
	}

	func[state](this);

	reverse = (target.x < GetCenter().x) ? false : true;
}
