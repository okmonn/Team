#pragma once
#include <memory>

enum D3D12_COMMAND_LIST_TYPE : int;
struct ID3D12CommandQueue;
class Device;

class Queue
{
public:
	// �R���X�g���N�^
	Queue(std::weak_ptr<Device>dev, const D3D12_COMMAND_LIST_TYPE& type = (D3D12_COMMAND_LIST_TYPE)0);
	// �f�X�g���N�^
	~Queue();

	// �L���[�̎擾
	ID3D12CommandQueue* Get(void) const {
		return queue;
	}

private:
	// �L���[�̐���
	long CreateQueue(const D3D12_COMMAND_LIST_TYPE& type);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �L���[
	ID3D12CommandQueue* queue;
};
