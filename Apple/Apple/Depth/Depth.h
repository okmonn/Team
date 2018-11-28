#pragma once
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Device;
class List;

class Depth
{
public:
	// �R���X�g���N�^
	Depth(std::weak_ptr<Device>dev, const unsigned int& width, const unsigned int& height);
	// �f�X�g���N�^
	~Depth();

	// �[�x�̃N���A
	void Clear(std::shared_ptr<List>list);

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(void) const {
		return heap;
	}
	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(void) const {
		return rsc;
	}

private:
	// �q�[�v�̐���
	long CreateHeap(void);

	// ���\�[�X�̐���
	long CreateRsc(const unsigned int& width, const unsigned int& height);

	// �r���[�̐���
	void CreateView(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	ID3D12Resource* rsc;
};