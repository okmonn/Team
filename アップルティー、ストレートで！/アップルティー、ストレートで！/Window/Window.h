#pragma once
#include "../etc/tstring.h"
#include "../etc/Vector2.h"

struct ID3D12DescriptorHeap;
struct ID3D12Resource;

class Window
{
public:
	// �R���X�g���N�^
	Window(const Vec2& size, void* parent);
	// �f�X�g���N�^
	~Window();

	// �^�C�g�����̕ύX
	void ChangeTitle(const std::tstring& title);

	// �E�B���h�E�n���h���̎擾
	void* Get(void) const {
		return handle;
	}
	// �E�B���h�E�T�C�Y�̎擾
	Vec2 GetSize(void) const {
		return size;
	}
	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(void);
	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(void);

private:
	// �E�B���h�E�̃R�[���o�b�N
#if _WIN64
	static long __stdcall WindowProc(void* hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam);
#else
	static long __stdcall WindowProc(void* hWnd, unsigned int message, long wParam, long lParam);
#endif

	// �E�B���h�E�̐���
	void Create(void* parent);

	// �萔�o�b�t�@�̐���
	void ConstantBuffer(void);


	// �E�B���h�E�T�C�Y
	Vec2 size;

	// �E�B���h�E�n���h��
	void* handle;

	// �E�B���h�E�C���X�^���X
	void* instance;

	// �E�B���h�E��
	const wchar_t* name;

	// �萔�o�b�t�@ID
	int constant;
};
