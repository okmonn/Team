#pragma once

class Input
{
public:
	// �f�X�g���N�^
	~Input();

	// �C���X�^���X�ϐ��̎擾
	static Input& Get(void) {
		static Input instance;
		return instance;
	}

	// �L�[�̓���
	bool InputKey(const int& i);

	// �g���K�[�̓���
	bool Triger(const int& i);

private:
	// �R���X�g���N�^
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;


	// ���݂̃L�[���
	int key[256];

	// �ߋ��̃L�[���
	int old[256];
};
