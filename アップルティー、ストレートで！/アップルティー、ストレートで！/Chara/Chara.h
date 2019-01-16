#pragma once
#include "../Typedef.h"
#include <memory>
#include <functional>
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
	// ���W�̃Z�b�g
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}
	// ���[�J�����W�̎擾
	Vec2f GetLocal(void) const {
		return lpos;
	}
	// ���[�J�����W�̃Z�b�g
	void SetLocal(const Vec2f& pos) {
		lpos = pos;
	}
	// �T�C�Y�̎擾
	Vec2f GetSize(void) const {
		return size;
	}
	// �T�C�Y�̃Z�b�g
	void SetSize(const Vec2f& size) {
		this->size = size;
	}
	// �X�e�[�^�X�̎擾
	std::string GetState(void) const {
		return state;
	}
	// �X�e�[�^�X�̃Z�b�g
	void SetState(const std::string& state);
	// ���]�t���O�̎擾
	bool GetReverse(void) const {
		return reverse;
	}
	// ���]�t���O�̃Z�b�g
	void SetReverse(const bool& flag) {
		reverse = flag;
	}

protected:
	// �A�j���[�V�����E��`���̓ǂݍ���
	void LoadInfo(const std::string& fileName);

	// �摜�̓ǂݍ���
	void LoadImg(const std::string& name, const std::string& fileName);

	// �A�j���[�^�[
	void Animator(const float& speed = 1.0f);

	// �A�j���[�V�����I���t���O
	bool CheckAnimEnd(void);

	// �摜�̕`��
	void DrawImg(const std::string& name, const Vec2f& pos, const Vec2f& size, const float& alpha = 1.0f, const bool& turnY = false);

	// �摜�̍폜
	void Delete(const std::string& name);
	void Delete(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;

	// ���W
	Vec2f pos;

	// ���[�J�����W
	Vec2f lpos;

	// �T�C�Y
	Vec2f size;

	// �X�e�[�^�X
	std::string state;

	// info�t�@�C����
	std::string info;

	// �z��p�C���f�b�N�X
	unsigned int index;

	// �ړ����x
	float speed;

	// �t���[��
	float flam;

	// ���]�t���O
	bool reverse;

	// �摜ID
	std::unordered_map<std::string, int>image;
};
