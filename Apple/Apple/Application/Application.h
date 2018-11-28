#pragma once
#include <memory>

class Window;
class Union;

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

	// ���j�I��
	std::shared_ptr<Union>un;
};
