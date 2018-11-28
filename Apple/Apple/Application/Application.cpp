#include "Application.h"
#include "../Window/Window.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include <Windows.h>

// �R���X�g���N�^
Application::Application()
{
	Create();
}

// �f�X�g���N�^
Application::~Application()
{
}

// �N���X�̐���
void Application::Create(void)
{
	win   = std::make_shared<Window>();
	input = std::make_shared<Input>(win);
	un    = std::make_shared<Union>(win);
}

// ���b�Z�[�W�̊m�F
bool Application::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//�Ăяo�����X���b�h�����L���Ă���E�B���h�E�ɑ��M���ꂽ���b�Z�[�W�ۗ̕�����Ă��镨���擾
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
		TranslateMessage(&msg);
		//1�̃E�B�h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
		DispatchMessage(&msg);
	}
	else
	{
		un->Draw();
	}

	return true;
}

// �L�[�̓���
bool Application::InputKey(const int & i)
{
	return input->CheckKey(i);
}
