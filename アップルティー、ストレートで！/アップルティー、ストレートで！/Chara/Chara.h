#pragma once
#include "../Typedef.h"
#include <memory>
#include <functional>
#include <unordered_map>

class Camera;
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
	// �T�C�Y�̎擾
	Vec2f GetSize(void) const {
		return size;
	}
	// ���S���W�̎擾
	Vec2f GetCenter(void) const {
		return pos + size / 2.0f;
	}
	// �X�e�[�^�X�̎擾
	std::string GetState(void) const {
		return state;
	}
	// �X�e�[�^�X�̃Z�b�g
	void SetState(const std::string& state);
	// �������`�̎擾
	std::vector<HitRect<Vec2f>> GetRect(void);
	// �̗͂̎擾
	unsigned int GetHp(void) const {
		return hp;
	}
	// �̗͂̃Z�b�g
	void SetHp(const unsigned int& hp) {
		this->hp = hp;
	}
	// ���]�t���O�̎擾
	bool GetReverse(void) const {
		return reverse;
	}
	// ���]�t���O�̃Z�b�g
	void SetReverse(const bool& flag) {
		reverse = flag;
	}
	// ���S�t���O�̎擾
	bool GetDead(void) const {
		return dead;
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
	void DrawImg(const std::string& name, const float& alpha = 1.0f, const bool& turnY = false);

	// �������`�̕`��
	void DrawRect(void);

	// ���[�J�����W�̍X�V
	void UpDataLocal(void);

	// �摜�̍폜
	void Delete(const std::string& name);
	void Delete(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;

	// �J����
	std::weak_ptr<Camera>cam;

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

	// �̗�
	unsigned int hp;

	// �z��p�C���f�b�N�X
	unsigned int index;

	// �ړ����x
	float speed;

	// �t���[��
	float flam;

	// ���]�t���O
	bool reverse;

	// ���S�t���O
	bool dead;

	// �摜ID
	std::unordered_map<std::string, int>image;
};
