#pragma once
#include "Character.h"
class Map;

class Player :
	public Character
{
public:
	// �R���X�g���N�^
	Player(std::weak_ptr<Input>in, std::weak_ptr<Union>un,std::weak_ptr<Map>map);
	// �f�X�g���N�^
	~Player();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:
	// �X�e�[�^�X���̏����̃Z�b�g
	void SetFunc(void);

	// �L�[�̓���
	bool CheckKey(const int& i);

	// �g���K�[�̓���
	bool Triger(const int& i);

	// �ҋ@���̏���
	void Wait(void);

	// �������̏���
	void Walk(void);

	// ������̏���
	void Avoid(void);

	// �U��1���̏���
	void Attack1(void);

	// �U��2���̏���
	void Attack2(void);

	// �X���C�f�B���O���̏���
	void Sliding(void);

	// �_���[�W���̏���
	void Damage(void);


	// �֐��|�C���^
	std::unordered_map<std::string, std::function<void(Player*)>>func;
	// �}�b�v���
	std::weak_ptr<Map>map;
};
