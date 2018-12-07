// �o�[�W����
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Input.h"
#include "../Window/Window.h"
#include "../etc/Release.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// �R���X�g���N�^
Input::Input(std::weak_ptr<Window>win) :
	win(win), input(nullptr), dev(nullptr)
{
	memset(&keys[0], 0, sizeof(keys));
	memset(&olds[0], 0, sizeof(olds));

	Init();
}

// �f�X�g���N�^
Input::~Input()
{
	Release(dev);
	Release(input);
}

// �C���v�b�g�̐���
long Input::CreateInput(void)
{
	auto hr = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&input), nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�C���v�b�g�̐����F���s\n"));
	}

	return hr;
}

// �L�[�f�o�C�X�̐���
long Input::CreateDev(void)
{
	auto hr = input->CreateDevice(GUID_SysKeyboard, &dev, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�L�[�f�o�C�X�̐����F���s\n"));
	}

	return hr;
}

// �L�[�t�H�[�}�b�g�̃Z�b�g
long Input::SetKeyFormat(void)
{
	auto hr = dev->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�L�[�t�H�[�}�b�g�̃Z�b�g�F���s\n"));
	}

	return hr;
}

// �L�[�̋������x���̃Z�b�g
long Input::SetKeyCooperative(void)
{
	auto hr = dev->SetCooperativeLevel(reinterpret_cast<HWND>(win.lock()->Get()), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�L�[�̋������x���̃Z�b�g�F���s\n"));
		return hr;
	}

	//���̓f�o�C�X�ւ̃A�N�Z�X�������擾
	dev->Acquire();

	return hr;
}

// ������
void Input::Init(void)
{
	CreateInput();
	CreateDev();
	SetKeyFormat();
	SetKeyCooperative();
}

// �L�[����
bool Input::CheckKey(const int & i)
{
	bool flag = false;

	//�L�[�����擾
	dev->GetDeviceState(sizeof(keys), &keys);

	if (keys[i] & 0x80)
	{
		flag = true;
	}

	olds[i] = keys[i];

	return flag;
}

// �L�[�g���K�[
bool Input::Triger(const int & i)
{
	bool flag = false;

	//�L�[�����擾
	dev->GetDeviceState(sizeof(keys), &keys);

	if ((keys[i] & 0x80) && !(olds[i] & 0x80))
	{
		flag = true;
	}

	olds[i] = keys[i];

	return flag;
}
