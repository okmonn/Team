#pragma once
#include "../etc/Vector2.h"
#include <memory>

class Application;
class Chara;

class Camera
{
public:
	// �R���X�g���N�^
	Camera(std::weak_ptr<Application> app);
	// �f�X�g���N�^
	~Camera();
	
	// ����
	void UpData(void);

	// �^�[�Q�b�g�̃Z�b�g
	void SetTarget(std::weak_ptr<Chara>target) {
		this->target = target;
	}
	// ���W�̎擾
	Vec2f GetPos(void) const {
		return pos;
	}
	// ���W�̃Z�b�g
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}

private:
	// �A�v���P�[�V����
	std::weak_ptr<Application> app;

	// �^�[�Q�b�g�L����
	std::weak_ptr<Chara>target;

	// ���W
	Vec2f pos;
};