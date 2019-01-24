#pragma once
#include "../etc/Vector2.h"
#include <vector>
#include <memory>

class Application;

class Map
{
public:
	// �R���X�g���N�^
	Map(std::weak_ptr<Application>app);
	// �f�X�g���N�^
	~Map();

	// �P�}�X���̃T�C�Y�̎擾
	Vec2f GetSize(void) const {
		return size;
	}
	// �}�X���̎擾
	Vec2 GetMass(void) const {
		return mass;
	}
	// �n�ʍ��W�̎擾
	float GetGround(void) const {
		return ground;
	}
	// �}�b�v�f�[�^�̎擾
	std::vector<int> GetData(void) const {
		return id;
	}

private:
	//	������
	void Init(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;

	// 1�}�X�̃T�C�Y
	Vec2f size;

	// �}�X��
	Vec2 mass;

	// �n�ʈʒu
	float ground;

	// �}�b�v�f�[�^
	std::vector<int>id;
};
