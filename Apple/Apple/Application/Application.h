#pragma once
#include "../etc/KeyData.h"
#include <memory>

class Window;
class Input;
class Union;
class Effector;
class Sound;

class Application
{
public:
	// �f�X�g���N�^
	~Application();

	// �C���X�^���X�ϐ��̎擾
	static Application& Get(void) {
		static Application instance;
		return instance;
	}

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void);

	// �L�[�̓���
	bool InputKey(const int& i);

	// �`��
	void Draw(void);

private:
	// �R���X�g���N�^
	Application();
	Application(const Application&) {
	}
	void operator=(const Application&) {
	}

	// �N���X�̐���
	void Create(void);


	// �E�B���h�E
	std::shared_ptr<Window>win;

	// �C���v�b�g
	std::shared_ptr<Input>input;

	// ���j�I��
	std::shared_ptr<Union>un;

	// �G�t�F�N�^�[
	std::shared_ptr<Effector>effector;

	// �T�E���h
	std::shared_ptr<Sound>sound;
};
