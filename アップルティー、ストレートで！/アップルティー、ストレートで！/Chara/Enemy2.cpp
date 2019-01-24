#include "Enemy2.h"
#include "../Camera/Camera.h"
#include "Player.h"
#include "../Application/Application.h"

// �ڍs�I�t�Z�b�g
#define OFFSET 1.0f

// �R���X�g���N�^
Enemy2::Enemy2(std::weak_ptr<Application> app, std::weak_ptr<Camera> cam, std::weak_ptr<Player>pl, const Vec2f& pos, const Vec2f& size)
{
	this->app	= app;
	this->cam	= cam;
	this->pl	= pl;
	this->pos	= pos;
	this->lpos	= pos;
	this->size	= size;

	hp = 10;

	LoadImg("1", "_rsc/img/Enemy2.png");
	LoadInfo("_rsc/info/enemy2.info");
	SetFunc();
}

// �f�X�g���N�^
Enemy2::~Enemy2()
{
	Delete();
}

// �X�e�[�^�X���̏����̃Z�b�g
void Enemy2::SetFunc(void) 
{
	func.clear();

	func["wait"]   = &Enemy2::Wait;
	func["walk"]   = &Enemy2::Walk;
	func["attack"] = &Enemy2::Attack;
	func["damage"] = &Enemy2::Damage;
	func["dead"]   = &Enemy2::Dead;
}

// �ҋ@���̏���
void Enemy2::Wait(void) 
{
	if (state != "wait")
	{
		return;
	}

	// Player�̒��_
	target = pl.lock()->GetCenter();

	// �ړ�
	Vec2f tmp = GetCenter() - target;
	if ( tmp.x < 240.0f
		|| tmp.y < 270.0f) 
	{
		SetState("walk");
	}

	// �U������
	if (GetCenter().y >= pl.lock()->GetCenter().y
		&& GetCenter().y <= (pl.lock()->GetPos().y + pl.lock()->GetSize().y))
	{
		if (reverse)
		{
			if ((pos.x + size.x) <= target.x
				&& (pos.x + (size.x * 2)) >= target.x)
			{
				if (pl.lock()->GetState() != "damage")	// �N���U�ߑ΍�
				{
					SetState("attack");
				}
			}
		}
		else
		{
			if (pos.x >= target.x
				&& (pos.x - size.x) <= target.x)
			{
				if (pl.lock()->GetState() != "damage")	// �N���U�ߑ΍�
				{
					SetState("attack");
				}
			}
		}
	}
}

// �ړ����̏���
void Enemy2::Walk(void) 
{
	if (state != "walk")
	{
		return;
	}
	
	if (GetCenter().x > target.x)
	{
		pos.x -= speed;
	}
	else if (GetCenter().x < target.x)
	{
		pos.x += speed;
	}

	if (GetCenter().y > target.y)
	{
		pos.y -= speed;
	}
	else if (GetCenter().y < target.y)
	{
		pos.y += speed;
	}

	// ���_
	target = pl.lock()->GetCenter();

	if (GetCenter().y >= target.y
		&& GetCenter().y <= (pl.lock()->GetPos().y + pl.lock()->GetSize().y))
	{
		if (reverse)
		{
			if ((pos.x + size.x) <= target.x
				&& (pos.x + (size.x * 2)) >= target.x)
			{
				SetState("attack");
			}
		}
		else
		{
			if (pos.x >= target.x
				&& (pos.x - size.x) <= target.x)
			{
				SetState("attack");
			}
		}
	}

	if (CheckAnimEnd())
	{
		SetState("wait");
	}
}

// �U�����̏���
void Enemy2::Attack(void) 
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
void Enemy2::Damage(void) 
{
	if (state != "damage")
	{
		return;
	}
}

// ���S���̏���
void Enemy2::Dead(void) 
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
void Enemy2::Draw(void)
{
	DrawImg("1");

#if _DEBUG
	DrawRect();
#endif
}

// ����
void Enemy2::UpData(void) 
{
	UpDataLocal();
	Animator();
	func[state](this);
	CheckHit();

	reverse = (target.x < GetCenter().x) ? false : true;
}