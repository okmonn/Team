#pragma once
#include "Enemy.h"

class Enemy1 :
	public Enemy
{
public:
	// �R���X�g���N�^
	Enemy1(std::weak_ptr<Application>app, const Vec2f& pos = 0.0f, const Vec2f& size = 100.0f);
	// �f�X�g���N�^
	~Enemy1();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:

};
