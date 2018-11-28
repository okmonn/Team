#pragma once
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Device;
class List;
class Swap;

class Render
{
public:
	// �R���X�g���N�^
	Render(std::weak_ptr<Device>dev, std::weak_ptr<Swap>swap);
	// �f�X�g���N�^
	~Render();

	// �����_�[�^�[�Q�b�g�̃N���A
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(void) const {
		return heap;
	}
	// ���\�[�X�̎擾
	std::vector<ID3D12Resource*>GetRsc(void) const {
		return rsc;
	}
	// ���\�[�X�̎擾
	ID3D12Resource* Get(void) const;

private:
	// �q�[�v�̐���
	long CreateHeap(const unsigned int& num);

	// ���\�[�X�̐���
	long CreateRsc(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �X���b�v
	std::weak_ptr<Swap>swap;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	std::vector<ID3D12Resource*>rsc;
};
