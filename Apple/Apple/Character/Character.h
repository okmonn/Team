#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

class Input;
class Union;

class Character
{
	// �ǂݍ��݃L�����N�^�[�̋�`���
	struct Rect {
		//��`���W
		Vec2f pos;
		//��`�T�C�Y
		Vec2f size;
	};

	// �ǂݍ��݃L�����N�^�[���
	struct Info {
		//�X�e�[�^�X�̕�����
		unsigned char stNameNum;
		//�X�e�[�^�X
		std::string st;
		//�A�j���[�V��������
		float animTime;
		//�����A�j���[�V���������邩
		unsigned char animNum;
	};

public:
	// �R���X�g���N�^
	Character();
	// �f�X�g���N�^
	virtual ~Character();

	// ����
	virtual void UpData(void) = 0;

	// �`��
	virtual void Draw(void) = 0;

	// ���[���h���W�̎擾
	Vec2f GetPos(void) const {
		return pos;
	}
	// ���[�����W�̃Z�b�g
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}
	// ���[�J�����W�̎擾
	Vec2f GetLocal(void) const {
		return local;
	}
	// ���[�J�����W�̃Z�b�g
	void SetLocal(const Vec2f& local) {
		this->local = local;
	}
	// �T�C�Y�̎擾
	Vec2f GetSize(void) const {
		return size;
	}

	// �X�e�[�^�X�̎擾
	std::string GetState(void) const {
		return st;
	}
	// �X�e�[�^�X�̃Z�b�g
	void SetState(const std::string& st);

protected:
	// ��`���̓ǂݍ���
	int LoadInfo(const std::string& fileName);

	// �摜�̓ǂݍ���
	void Load(const std::string& fileName, const std::string& name);

	// �A�j���[�V�����Ǘ�
	void Animator(const float& speed = 1.0f);

	// �A�j���[�V�����I���m�F
	bool CheckAnimEnd(void);

	// �摜�̕`��
	void DrawImg(const std::string& name, const float& x, const float& y, const float& sizeX, const float& sizeY,
		const float& alpha = 1.0f, const bool& turnY = false);


	// �C���v�b�g
	std::weak_ptr<Input>in;

	// ���j�I��
	std::weak_ptr<Union>un;

	// ���[���h���W
	Vec2f pos;

	// ���[�J�����W
	Vec2f local;

	// �T�C�Y
	Vec2f size;

	// �ړ����x
	float speed;

	// �A�j���[�V�����t���[��
	float flam;

	// �A�j���[�V�����C���f�b�N�X
	unsigned int index;

	// �X�e�[�^�X
	std::string st;

	// ���]�t���O
	bool reverse;

	// ��`���
	std::unordered_map<std::string, std::vector<Rect>>rect;

	// �A�j���[�V�������x
	std::unordered_map<std::string, float>animTime;

	// �摜ID
	std::unordered_map<std::string, int>img;
};
