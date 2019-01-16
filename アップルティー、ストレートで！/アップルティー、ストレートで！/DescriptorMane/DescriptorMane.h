#pragma once
#include <memory>
#include <unordered_map>

enum D3D12_DESCRIPTOR_HEAP_FLAGS : int;
enum D3D12_DESCRIPTOR_HEAP_TYPE : int;
enum D3D12_RESOURCE_STATES :int;
struct D3D12_HEAP_PROPERTIES;
struct D3D12_RESOURCE_DESC;
struct D3D12_CLEAR_VALUE;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;

class Swap;

enum RSC_TYPE {
	RSC_TYPE_NON, 
	RSC_TYPE_RTV,
	RSC_TYPE_DSV,
	RSC_TYPE_CBV,
	RSC_TYPE_SRV
};

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
	long CreateHeap(int& addr, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const size_t& num, const D3D12_DESCRIPTOR_HEAP_TYPE& type);

	// ���\�[�X�̐���
	long CreateRsc(int& addr, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, const D3D12_RESOURCE_STATES& state, const D3D12_CLEAR_VALUE* clear = nullptr);
	// ���\�[�X�̐���
	long CreateRsc(int& addr, std::weak_ptr<Swap>swap, const unsigned int& index);

	// RTV�̐���
	void RTV(int& heapAddr, int& rscAddr, const unsigned int& index = 0);

	// DSV�̐���
	void DSV(int& heapAddr, int& rscAddr, const unsigned int& index = 0);

	// CBV�̐���
	void CBV(int& heapAddr, int& rscAddr, const size_t& size, const unsigned int& index = 0);

	// SRV�̐���
	void SRV(int& heapAddr, int& rscAddr, const unsigned int& index = 0);

	// UAV�̐���
	void UAV(int& heapAddr, int& rscAddr, const size_t& stride, const size_t& num, const unsigned int& index = 0);

	// �q�[�v�̍폜
	void DeleteHeap(int& addr);

	// ���\�[�X�̍폜
	void DeleteRsc(int& addr);

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(int& addr) {
		return heap[&addr];
	}
	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(int& addr) {
		return rsc[&addr];
	}

private:
	// �R���X�g���N�^
	DescriptorMane();
	DescriptorMane(const DescriptorMane&) = delete;
	void operator=(const DescriptorMane&) = delete;


	// �q�[�v
	std::unordered_map<int*, ID3D12DescriptorHeap*>heap;

	// ���\�[�X
	std::unordered_map<int*, ID3D12Resource*>rsc;
};
