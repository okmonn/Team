#include "Primitive.h"
#include "../DescriptorMane/DescriptorMane.h"
#include "../Window/Window.h"
#include "../Device/Device.h"
#include "../List/List.h"
#include "../Root/Root.h"
#include "../Pipe/Pipe.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Primitive::Primitive() : descMane(DescriptorMane::Get()),
	constant(0), vRsc(0)
{
	vertex.clear();
}

// �f�X�g���N�^
Primitive::~Primitive()
{
}

// �萔���\�[�X�̐���
long Primitive::CreateRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 1;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	prop.VisibleNodeMask      = 1;

	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (sizeof(DirectX::XMFLOAT2) + 0xff) &~0xff;

	auto hr = descMane.CreateRsc(dev, constant, prop, desc);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�v���~�e�B�u�p�萔���\�[�X�̐����F���s\n"));
	}

	return hr;
}

// �萔�o�b�t�@�r���[�̐���
void Primitive::CreateView(void)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
	desc.BufferLocation = descMane.GetRsc(constant)->GetGPUVirtualAddress();
	desc.SizeInBytes    = (sizeof(DirectX::XMFLOAT2) + 0xff) &~0xff;

	dev.lock()->Get()->CreateConstantBufferView(&desc, descMane.GetHeap(constant)->GetCPUDescriptorHandleForHeapStart());
}

// �萔�̃}�b�v
long Primitive::Map(void)
{
	void* data = nullptr;
	auto hr = descMane.GetRsc(constant)->Map(0, nullptr, &data);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�v���~�e�B�u�p�萔���\�[�X�̃}�b�v�F���s\n"));
		return hr;
	}

	DirectX::XMFLOAT2 winSize = { static_cast<float>(win.lock()->GetX()), static_cast<float>(win.lock()->GetY()) };
	memcpy(data, &winSize, sizeof(DirectX::XMFLOAT2));

	descMane.GetRsc(constant)->Unmap(0, nullptr);

	return hr;
}

// ���_���\�[�X�̐���
long Primitive::CreateVrsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 1;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	prop.VisibleNodeMask      = 1;

	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1,0 };
	desc.Width            = sizeof(prm::Vertex) * vertex.size();

	return descMane.CreateRsc(dev, vRsc, prop, desc);
}
