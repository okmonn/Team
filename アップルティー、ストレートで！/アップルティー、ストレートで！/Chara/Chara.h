#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <memory>
#include <unordered_map>

class Application;

class Chara
{
public:
	// �R���X�g���N�^
	Chara();
	// �f�X�g���N�^
	virtual ~Chara();

	// �`��
	virtual void Draw(void) = 0;

	// ����
	virtual void UpData(void) = 0;

	// ���W�̎擾
	Vec2f GetPos(void) const {
		return pos;
	}
	// ���[�J�����W�̎擾
	Vec2f GetLocal(void) const {
		return lpos;
	}
	// �T�C�Y�̎擾
	Vec2f GetSize(void) const {
		return size;
	}

protected:
	// �摜�̓ǂݍ���
	void LoadImg(const std::string& name, const std::string& fileName);

	// �摜�̕`��
	void Draw(const std::string& name, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);

	// �摜�̍폜
	void Delete(const std::string& name);
	void Delete(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;

	// �摜ID
	std::unordered_map<std::string, int>image;

	// ���W
	Vec2f pos;

	// ���[�J�����W
	Vec2f lpos;

	// �T�C�Y
	Vec2f size;
};
