#pragma once
#include "../etc/KeyData.h"
#include <memory>

struct IDirectInput8W;
struct IDirectInputDevice8W;

// �L�[�ő吔
#define KEY_MAX 256

class Window;

class Input
{
public:
	// �R���X�g���N�^
	Input(std::weak_ptr<Window>win);
	// �f�X�g���N�^
	~Input();

	// �L�[����
	bool CheckKey(const int& i);

	// �L�[�g���K�[
	bool Triger(const int& i);

private:
	// �C���v�b�g�̐���
	long CreateInput(void);

	// �L�[�f�o�C�X�̐���
	long CreateDev(void);

	// �L�[�t�H�[�}�b�g�̃Z�b�g
	long SetKeyFormat(void);

	// �L�[�̋������x���̃Z�b�g
	long SetKeyCooperative(void);

	// ������
	void Init(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �C���v�b�g
	IDirectInput8W* input;

	// �C���v�b�g�f�o�C�X
	IDirectInputDevice8W* dev;

	// ���݂̃L�[���
	unsigned char keys[KEY_MAX];

	// ���O�̃L�[���
	unsigned char olds[KEY_MAX];
};
