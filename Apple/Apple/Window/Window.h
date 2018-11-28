#pragma once
#include "../etc/tString.h"

class Window
{
public:
	// �R���X�g���N�^�@
	Window(const unsigned int& width = 640, const unsigned int& height = 480);
	// �f�X�g���N�^
	~Window();

	// �^�C�g�����̕ύX
	void ChangeTitle(const std::tstring& title);

	// �E�B���h�E�n���h���̎擾
	void* Get(void) const {
		return handle;
	}
	// �E�B���h�E�����̎擾
	unsigned int GetX(void) const {
		return width;
	}
	// �E�B���h�E�c��
	unsigned int GetY(void) const {
		return height;
	}

private:
	// �E�B���h�E�̃R�[���o�b�N
#if _WIN64
	static long __stdcall WindowProc(void* hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam);
#else
	static long __stdcall WindowProc(void* hWnd, unsigned int message, long wParam, long lParam);
#endif

	// �E�B���h�E�̐���
	void Create(void);


	// �E�B���h�E�n���h��
	void* handle;

	// �E�B���h�E�C���X�^���X
	void* instance;

	// �E�B���h�E��
	const wchar_t* name;

	// �E�B���h�E�̉���
	unsigned int width;

	// �E�B���h�E�̏c��
	unsigned int height;
};
