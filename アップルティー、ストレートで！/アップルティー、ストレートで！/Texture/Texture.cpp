#include "Texture.h"
#include "TexLoader.h"
#include "../Device/Device.h"
#include "../DescriptorMane/DescriptorMane.h"
#include "../Window/Window.h"
#include "../List/List.h"
#include "../Root/Root.h"
#include "../Pipe/Pipe.h"
#include "../etc/Release.h"

// ���\�[�X��
#define RSC_MAX 2

// �R���X�g���N�^
Texture::Texture(std::weak_ptr<Window> win, std::weak_ptr<Root> root, std::weak_ptr<Pipe> pipe) : win(win), root(root), pipe(pipe),
	data(nullptr), rsc(nullptr), constant(0), vRsc(0)
{
	VertexBuffer();
	ConstantBuffer();
}

// �f�X�g���N�^
Texture::~Texture()
{
	DescriptorMane::Get().GetRsc(constant)->Unmap(0, nullptr);
	DescriptorMane::Get().DeleteRsc(constant);
	DescriptorMane::Get().DeleteRsc(vRsc);
	DescriptorMane::Get().DeleteHeap(constant);
}

// ���_�o�b�t�@�̐���
void Texture::VertexBuffer(void)
{
	tex::Vertex vertex[] = {
		{ { 0.0f,                           0.0f,                          0.0f }, { 0.0f, 0.0f } },
		{ { (float)win.lock()->GetSize().x, 0.0f,                          0.0f }, { 1.0f, 0.0f } },
		{ { 0.0f,                          (float)win.lock()->GetSize().y, 0.0f }, { 0.0f, 1.0f } },
		{ { (float)win.lock()->GetSize().x,(float)win.lock()->GetSize().y, 0.0f }, { 1.0f, 1.0f } }
	};

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 0;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	prop.VisibleNodeMask      = 0;

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
	desc.Width            = sizeof(tex::Vertex) * _countof(vertex);

	DescriptorMane::Get().CreateRsc(vRsc, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	void* data = nullptr;

	auto hr = DescriptorMane::Get().GetRsc(vRsc)->Map(0, nullptr, &data);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�e�N�X�`���p���_���\�[�X�̃}�b�v�F���s\n"));
		return;
	}

	memcpy(data, &vertex[0], sizeof(tex::Vertex) * _countof(vertex));

	DescriptorMane::Get().GetRsc(vRsc)->Unmap(0, nullptr);
}

// �萔�o�b�t�@�̐���
void Texture::ConstantBuffer(void)
{
	DescriptorMane::Get().CreateHeap(constant, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, RSC_MAX,
		D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 0;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	prop.VisibleNodeMask      = 0;

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
	desc.Width            = (sizeof(tex::CbvInfo) + 0xff) &~0xff;

	DescriptorMane::Get().CreateRsc(constant, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	DescriptorMane::Get().CBV(constant, constant, (sizeof(tex::CbvInfo) + 0xff) & ~0xff);

	auto hr = DescriptorMane::Get().GetRsc(constant)->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�e�N�X�`���p�萔���\�[�X�̃}�b�v�F���s\n"));
	}
}

// �V�F�[�_�o�b�t�@�̐���
void Texture::ShaderBuffer(void)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC desc{};
	desc.Format                    = rsc->GetDesc().Format;
	desc.ViewDimension             = D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels       = 1;
	desc.Texture2D.MostDetailedMip = 0;
	desc.Shader4ComponentMapping   = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	auto handle = DescriptorMane::Get().GetHeap(constant)->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().GetDev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	Device::Get().GetDev()->CreateShaderResourceView(rsc, &desc, handle);
}

// �T�u���\�[�X�ɏ�������
long Texture::WriteSub(const std::string& fileName)
{
	D3D12_BOX box{};
	box.back   = 1;
	box.bottom = rsc->GetDesc().Height;
	box.front  = 0;
	box.left   = 0;
	box.right  = static_cast<unsigned int>(rsc->GetDesc().Width);
	box.top    = 0;

	auto hr = rsc->WriteToSubresource(0, &box, &TexLoader::Get().GetDecode(fileName)[0], static_cast<unsigned int>(sub.lock()->RowPitch), static_cast<unsigned int>(sub.lock()->SlicePitch));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�V�F�[�_���\�[�X�̃T�u�ւ̏������݁F���s"));
	}

	return hr;
}

// �ǂݍ���
void Texture::Load(const std::string & fileName)
{
	TexLoader::Get().Load(fileName);
	rsc = TexLoader::Get().GetRsc(fileName);
	sub = TexLoader::Get().GetSub(fileName);

	ShaderBuffer();
	WriteSub(fileName);
}

// �`�揀��
void Texture::SetDraw(const DirectX::XMFLOAT2 & pos, const DirectX::XMFLOAT2 & size, const DirectX::XMFLOAT2 & uvPos, const DirectX::XMFLOAT2 & uvSize, 
	const float & alpha, const bool & turnX, const bool & turnY)
{
	XMStoreFloat4x4(&data->matrix,
		DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat2(
			&DirectX::XMFLOAT2(size.x / static_cast<float>(win.lock()->GetSize().x), size.y / static_cast<float>(win.lock()->GetSize().y))))
		* DirectX::XMMatrixTranslationFromVector(
			DirectX::XMLoadFloat2(&DirectX::XMFLOAT2(pos.x, pos.y)))
	);
	data->uvPos   = uvPos;
	data->uvSize  = uvSize;
	data->reverse = { (turnX) ? 1.0f : 0.0f, (turnY) ? 1.0f : 0.0f };
	data->alpha   = alpha;
}

// �`��
void Texture::Draw(std::weak_ptr<List> list)
{
	list.lock()->SetRoot(root.lock()->Get());
	list.lock()->SetPipe(pipe.lock()->Get());

	D3D12_VERTEX_BUFFER_VIEW view{};
	view.BufferLocation = DescriptorMane::Get().GetRsc(vRsc)->GetGPUVirtualAddress();
	view.SizeInBytes    = static_cast<unsigned int>(DescriptorMane::Get().GetRsc(vRsc)->GetDesc().Width);
	view.StrideInBytes  = sizeof(tex::Vertex);
	list.lock()->SetVertexBufferView(view);

	auto heap = DescriptorMane::Get().GetHeap(constant);
	list.lock()->SetHeap(&heap, 1);
	for (int i = 0; i < RSC_MAX; ++i)
	{
		list.lock()->SetRootTable(i, heap, i);
	}

	heap = win.lock()->GetHeap();
	list.lock()->SetHeap(&heap, 1);
	list.lock()->SetRootTable(2, heap);

	list.lock()->SetTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	list.lock()->DrawVertex((view.SizeInBytes / view.StrideInBytes));
}
