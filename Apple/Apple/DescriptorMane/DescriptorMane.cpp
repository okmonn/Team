#include "DescriptorMane.h"
#include "../Device/Device.h"
#include "../etc/Release.h"
#include <dxgi1_6.h>

// �R���X�g���N�^
DescriptorMane::DescriptorMane()
{
	heap.clear();
	rsc.clear();
}

// �f�X�g���N�^
DescriptorMane::~DescriptorMane()
{
	for (auto itr = rsc.begin(); itr != rsc.end(); ++itr)
	{
		Release(itr->second);
	}
	for (auto itr = heap.begin(); itr != heap.end(); ++itr)
	{
		Release(itr->second);
	}
}

// �q�[�v�̐���
long DescriptorMane::CreateHeap(std::weak_ptr<Device>dev, int & i, const D3D12_DESCRIPTOR_HEAP_FLAGS & flag, const unsigned int & num, const D3D12_DESCRIPTOR_HEAP_TYPE & type)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = flag;
	desc.NodeMask       = 0;
	desc.NumDescriptors = num;
	desc.Type           = type;

	auto hr = dev.lock()->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap[&i]));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�q�[�v�̐����F���s\n"));
	}

	return hr;
}

// ���\�[�X�̐���
long DescriptorMane::CreateRsc(std::weak_ptr<Device>dev, int & i, const D3D12_HEAP_PROPERTIES & prop, const D3D12_RESOURCE_DESC & desc, D3D12_CLEAR_VALUE * clear, const D3D12_RESOURCE_STATES & state)
{
	auto hr = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&desc, state, clear, IID_PPV_ARGS(&rsc[&i]));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���\�[�X�̐����F���s\n"));
	}

	return hr;
}

// ���\�[�X�̍폜
void DescriptorMane::DeleteRsc(int & i)
{
	if (rsc.find(&i) != rsc.end())
	{
		Release(rsc[&i]);
		rsc.erase(rsc.find(&i));
	}
}

// �q�[�v�̍폜
void DescriptorMane::DeleteHeap(int & i)
{
	if (heap.find(&i) != heap.end())
	{
		Release(heap[&i]);
		heap.erase(heap.find(&i));
	}
}
