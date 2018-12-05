#pragma once
#include <map>
#include <memory>

enum D3D12_DESCRIPTOR_HEAP_FLAGS : int;
enum D3D12_DESCRIPTOR_HEAP_TYPE : int;
enum D3D12_RESOURCE_STATES:int;
struct D3D12_HEAP_PROPERTIES;
struct D3D12_RESOURCE_DESC;
struct D3D12_CLEAR_VALUE;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Device;

class DescriptorMane
{
public:
	// �f�X�g���N�^
	~DescriptorMane();

	// �C���X�^���X�ϐ��̎擾
	static DescriptorMane& Get(void) {
		static DescriptorMane instance;
		return instance;
	}

	// �q�[�v�̐���
	long CreateHeap(std::weak_ptr<Device>dev, int& i, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag = static_cast<D3D12_DESCRIPTOR_HEAP_FLAGS>(0),
		const unsigned int& num = 1, const D3D12_DESCRIPTOR_HEAP_TYPE& type = static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(0));

	// ���\�[�X�̐���
	long CreateRsc(std::weak_ptr<Device>dev, int& i, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, D3D12_CLEAR_VALUE* clear = nullptr,
		const D3D12_RESOURCE_STATES& state = static_cast<D3D12_RESOURCE_STATES>(2755));

	// ���\�[�X�̍폜
	void DeleteRsc(int& i);
	// �q�[�v�̍폜
	void DeleteHeap(int& i);

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(int& i) {
		return heap[&i];
	}
	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(int& i) {
		return rsc[&i];
	}

private:
	// �R���X�g���N�^
	DescriptorMane();
	DescriptorMane(const DescriptorMane&) {
	}
	void operator=(const DescriptorMane&) {
	}


	// �q�[�v
	std::map<int*, ID3D12DescriptorHeap*>heap;

	// ���\�[�X
	std::map<int*, ID3D12Resource*>rsc;
};
