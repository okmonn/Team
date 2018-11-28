#include "Render.h"
#include "../Device/Device.h"
#include "../List/List.h"
#include "../Swap/Swap.h"
#include "../etc/Release.h"
#include <dxgi1_6.h>

const float color[] = {
	1.0f, 1.0f, 1.0f, 1.0f
};

// �R���X�g���N�^
Render::Render(std::weak_ptr<Device> dev, std::weak_ptr<Swap> swap) : 
	dev(dev), swap(swap), heap(nullptr)
{
	rsc.clear();

	CreateRsc();
}

// �f�X�g���N�^
Render::~Render()
{
	for (auto& i : rsc)
	{
		Release(i);
	}

	Release(heap);
}

// �q�[�v�̐���
long Render::CreateHeap(const unsigned int & num)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	desc.NodeMask       = 0;
	desc.NumDescriptors = num;
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	auto hr = dev.lock()->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�����_�[�p�q�[�v�̐����F���s\n"));
	}

	return hr;
}

// ���\�[�X�̐���
long Render::CreateRsc(void)
{
	DXGI_SWAP_CHAIN_DESC1 tmp{};
	swap.lock()->Get()->GetDesc1(&tmp);

	CreateHeap(tmp.BufferCount);

	rsc.resize(tmp.BufferCount);

	D3D12_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format               = tmp.Format;
	desc.ViewDimension        = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice   = 0;
	desc.Texture2D.PlaneSlice = 0;

	auto hr = S_OK;
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	for (unsigned int i = 0; i < rsc.size(); ++i)
	{
		hr = swap.lock()->Get()->GetBuffer(i, IID_PPV_ARGS(&rsc[i]));
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n�����_�[�p���\�[�X�̐����F���s\n"));
			break;
		}

		//�����_�[�^�[�Q�b�g�̐���
		dev.lock()->Get()->CreateRenderTargetView(rsc[i], &desc, handle);

		//�n���h���ʒu�̍X�V
		handle.ptr += dev.lock()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	return hr;
}

// �����_�[�^�[�Q�b�g�̃N���A
void Render::Clear(std::shared_ptr<List>list, ID3D12DescriptorHeap * depth)
{
	//�q�[�v�̐擪�n���h���̎擾
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += dev.lock()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * swap.lock()->Get()->GetCurrentBackBufferIndex();

	//�����_�[�^�[�Q�b�g�̃Z�b�g
	list->GetList()->OMSetRenderTargets(1, &handle, false, &depth->GetCPUDescriptorHandleForHeapStart());

	//�����_�[�^�[�Q�b�g�̃N���A
	list->GetList()->ClearRenderTargetView(handle, color, 0, nullptr);
}

// ���\�[�X�̎擾
ID3D12Resource * Render::Get(void) const
{
	return rsc[swap.lock()->Get()->GetCurrentBackBufferIndex()];
}
