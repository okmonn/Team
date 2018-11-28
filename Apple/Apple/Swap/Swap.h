#pragma once
#include <memory>

struct IDXGISwapChain4;
class Window;
class Queue;

class Swap
{
public:
	// �R���X�g���N�^
	Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue);
	// �f�X�g���N�^
	~Swap();

	// �X���b�v�`�F�C���̎擾
	IDXGISwapChain4* Get(void) const {
		return swap;
	}

private:
	// �X���b�v�`�F�C���̐���
	long CreateSwap(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �L���[
	std::weak_ptr<Queue>queue;

	// �X���b�v�`�F�C��
	IDXGISwapChain4* swap;
};
