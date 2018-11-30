#include "Application.h"
#include "../Window/Window.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Effector/Effector.h"
#include "../Game/Game.h"
#include "../Sound/Sound.h"
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
	win      = std::make_shared<Window>();
	input    = std::make_shared<Input>(win);
	un       = std::make_shared<Union>(win);
	effector = std::make_shared<Effector>(un->GetDev(), L"Shader/Effect.hlsl");
	
	game     = std::make_shared<Game>(input, un);

	sound = std::make_shared<Sound>(effector);
	sound->Load("animal.wav");
	sound->Play(false);
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

	return true;
}

// �L�[�̓���
bool Application::InputKey(const int & i)
{
	return input->CheckKey(i);
}

// �`��
void Application::Draw(void)
{
	un->Clear();

	//�����ɕ`��E����
	game->Run();

	un->Execution();
}
