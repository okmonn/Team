#include "Xaudio2.h"
#include <xaudio2.h>
#include <tchar.h>

#pragma comment(lib, "xaudio2.lib")

// �R���X�g���N�^
Xaudio2::Xaudio2() : 
	audio(nullptr), mastering(nullptr)
{
	InitCom();
	Create();
	CreateMastering();
}

// �f�X�g���N�^
Xaudio2::~Xaudio2()
{
	if (mastering != nullptr)
	{
		mastering->DestroyVoice();
	}
	if (audio != nullptr)
	{
		audio->Release();
	}
	CoUninitialize();
}

// COM�̏�����
long Xaudio2::InitCom(void)
{
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nCOM�̏������F���s\n"));
	}

	return hr;
}

// Xaudio2�̐���
long Xaudio2::Create(void)
{
	auto hr = XAudio2Create(&audio);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nXaudio2�̐����F���s\n"));
	}

	return hr;
}

// �}�X�^�����O�̐���
long Xaudio2::CreateMastering(void)
{
	auto hr = audio->CreateMasteringVoice(&mastering);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�}�X�^�����O�̐����F���s\n"));
	}

	return hr;
}
