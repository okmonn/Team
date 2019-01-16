#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

class Application;

class Chara
{
	// �_�~�[�p�\����
	struct Dummy {
		//���W
		Vec2 pos;
		//�T�C�Y
		Vec2 size;
	};

	// �A�j���[�V�����E��`���
	struct Info {
		//�X�e�[�^�X���̕�����
		unsigned char stNameNum;
		//�X�e�[�^�X��
		std::string state;
		//�A�j���[�V��������
		float animTime;
		//�A�j���[�V������
		unsigned char animNum;
		//��`���
		std::vector<Dummy>rect;
	};

	// �A�j���[�V�����E��`���
	struct Rect {
		//���W
		Vec2f pos;
		//�T�C�Y
		Vec2f size;
	};

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
	// �A�j���[�V�����E��`���̏�������
	int WriteInfo(const std::string& fileName, const std::vector<Info>& info);

	// �A�j���[�V�����E��`���̓ǂݍ���
	int LoadInfo(const std::string& fileName);

	// �摜�̓ǂݍ���
	void LoadImg(const std::string& name, const std::string& fileName);

	// �A�j���[�^�[
	void Animator(const float& speed = 1.0f);

	// �A�j���[�V�����I���t���O
	bool CheckAnimEnd(void);

	// �摜�̕`��
	void DrawImg(const std::string& name, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& alpha = 1.0f, const bool& turnY = false);

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

	// �A�j���[�V��������
	std::unordered_map<std::string, float>animTime;

	// �A�j���[�V�����E��`���
	std::unordered_map<std::string, std::vector<Rect>>rect;
};
