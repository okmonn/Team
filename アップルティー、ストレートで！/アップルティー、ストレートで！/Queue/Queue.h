#pragma once

enum D3D12_COMMAND_LIST_TYPE : int;
struct ID3D12CommandQueue;
struct ID3D12CommandList;

class Queue
{
public:
	// �R���X�g���N�^
	Queue(const D3D12_COMMAND_LIST_TYPE& type);
	// �f�X�g���N�^
	~Queue();

	// ���s
	void Execution(ID3D12CommandList** list, const size_t& num);

	// �L���[�̎擾
	ID3D12CommandQueue* Get(void) const {
		return queue;
	}

private:
	// �L���[�̐���
	long Create(const D3D12_COMMAND_LIST_TYPE& type);


	// �L���[
	ID3D12CommandQueue* queue;
};
