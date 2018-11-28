#include <d3dcompiler.h>
#include "Effector.h"
#include "../Device/Device.h"
#include "../Queue/Queue.h"
#include "../List/List.h"
#include "../Fence/Fence.h"
#include "../Root/Root.h"
#include "../Pipe/Pipe.h"
#include "../etc/Release.h"

// ���\�[�X��
#define RSC_MAX 3

// �f�[�^�T�C�Y
#define DATA_MAX 44100

// �R���X�g���N�^
Effector::Effector(std::weak_ptr<Device>dev, const std::tstring & fileName) :
	dev(dev), root(nullptr), shader(nullptr), pipe(nullptr), heap(nullptr), index(0)
{
	param = {};
	info.clear();

	queue = std::make_shared<Queue>(dev, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	list  = std::make_unique<List>(dev, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	fence = std::make_unique<Fence>(dev, queue);

	CreateRoot(fileName);
	Init();
}

// �f�X�g���N�^
Effector::~Effector()
{
	for (auto itr = info.begin(); itr != info.end(); ++itr)
	{
		Release(itr->second.rsc);
	}

	Release(heap);
	Release(pipe);
	Release(shader);
	Release(root);
}

// ���[�g�V�O�l�`���̐���
long Effector::CreateRoot(const std::tstring & fileName)
{
	auto hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "CS", "cs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &shader, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�R���s���[�g�V�F�[�_�̓ǂݍ��݁F���s\n"));
		return hr;
	}

	ID3DBlob* sig = nullptr;

	hr = D3DGetBlobPart(shader->GetBufferPointer(), shader->GetBufferSize(), D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�R���s���[�g���[�g�V�O�l�`�����̎擾�F���s\n"));
		return hr;
	}

	hr = dev.lock()->Get()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�R���s���[�g���[�g�V�O�l�`���̐����F���s\n"));
	}

	Release(sig);

	return hr;
}

// �p�C�v���C���̐���
long Effector::CreatePipe(void)
{
	D3D12_COMPUTE_PIPELINE_STATE_DESC desc{};
	desc.CS.pShaderBytecode = shader->GetBufferPointer();
	desc.CS.BytecodeLength  = shader->GetBufferSize();
	desc.Flags              = D3D12_PIPELINE_STATE_FLAGS::D3D12_PIPELINE_STATE_FLAG_NONE;
	desc.NodeMask           = 0;
	desc.pRootSignature     = root;

	auto hr = dev.lock()->Get()->CreateComputePipelineState(&desc, IID_PPV_ARGS(&pipe));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�p�C�v���C���̐����F���s\n"));
	}

	return hr;
}

// �q�[�v�̐���
long Effector::CreateHeap(void)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask       = 0;
	desc.NumDescriptors = RSC_MAX;
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	auto hr = dev.lock()->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�G�t�F�N�g�p�q�[�v�̐����F���s\n"));
	}

	return hr;
}

// ���\�[�X�̐���
long Effector::CreateCbvRsc(const std::string & name, const unsigned int & size)
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
	desc.Width            = (size + 0xff) &~0xff;

	auto hr = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&info[name].rsc));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�G�t�F�N�g�pCBV���\�[�X�̐����F���s\n"));
		return hr;
	}

	info[name].index = index++;

	return hr;
}

// UAV���\�[�X�̐���
long Effector::CreateUavRsc(const std::string & name, const unsigned int & size)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.CreationNodeMask     = 1;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_L0;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_CUSTOM;
	prop.VisibleNodeMask      = 1;

	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (size + 0xff) &~0xff;

	auto hr = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS, nullptr, IID_PPV_ARGS(&info[name].rsc));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�G�t�F�N�g�pUAV���\�[�X�̐����F���s\n"));
		return hr;
	}

	info[name].index = index++;

	return hr;
}

// CBV�̐���
void Effector::CreateConstantView(const std::string & name, const unsigned int & size)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
	desc.BufferLocation = info[name].rsc->GetGPUVirtualAddress();
	desc.SizeInBytes    = (size + 0xff) &~0xff;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += info[name].index * dev.lock()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	dev.lock()->Get()->CreateConstantBufferView(&desc, handle);
}

// UAV�̐���
void Effector::CreateUnorderView(const std::string & name, const unsigned int & stride, const unsigned int & num)
{
	D3D12_UNORDERED_ACCESS_VIEW_DESC desc{};
	desc.ViewDimension              = D3D12_UAV_DIMENSION::D3D12_UAV_DIMENSION_BUFFER;
	desc.Format                     = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Buffer.NumElements         = num;
	desc.Buffer.StructureByteStride = stride;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += info[name].index * dev.lock()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
	dev.lock()->Get()->CreateUnorderedAccessView(info[name].rsc, nullptr, &desc, handle);
}

// �}�b�v
long Effector::Map(const std::string & name)
{
	D3D12_RANGE range{ 0, 1 };

	auto hr = info[name].rsc->Map(0, &range, reinterpret_cast<void**>(&info[name].data));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�G�t�F�N�g�p���\�[�X�̃}�b�v�F���s\n"));
	}

	return hr;
}

// CBV�̐���
void Effector::CBV(const std::string & name, const unsigned int & size)
{
	CreateCbvRsc(name, size);
	CreateConstantView(name, size);
	Map(name);
}

// UAV�̐���
void Effector::UAV(const std::string & name, const unsigned int & stride, const unsigned int & num)
{
	CreateUavRsc(name, stride * num);
	CreateUnorderView(name, stride, num);
	Map(name);
}

// ������
void Effector::Init(void)
{
	CreatePipe();

	CreateHeap();

	CBV("b0", sizeof(Param));
	UAV("u0", sizeof(float), DATA_MAX);
	UAV("u1", sizeof(float), DATA_MAX);
}

#include <DirectXMath.h>

// ���U�t�[���G�ϊ�
void DFT(void)
{
	//�~����
	const float p = 3.14159265f;
	//�f�[�^�T�C�Y
	int size = 64;

	//���f�[�^
	std::vector<float>origin(size);
	for (int i = 0; i < size; ++i)
	{
		origin[i] = 0.25f * sinf(2.0f * p * 250.0f * i / 8000);
	}

	auto hanning = [&](const int& index, const int& size)->float {
		return (size % 2 == 0) ?
			//����
			0.5f - 0.5f * cosf(2.0f * p * (float)index / (float)size) :
			//�
			0.5f - 0.5f * cosf(2.0f * p * ((float)index + 0.5f) / (float)size);
	};

	//����
	std::vector<float>real(size, 0.0f);
	//����
	std::vector<float>imag(size, 0.0f);

	memcpy(real.data(), origin.data(), sizeof(float) * size);

	//�_�~�[
	DirectX::XMFLOAT2 tmp;

	for (int i = 0; i < size; ++i)
	{
		for (int n = 0; n < size; ++n)
		{
			tmp.x = cosf(2.0f * p * i * n / size);
			tmp.y = -sinf(2.0f * p * i * n / size);

			real[i] += tmp.x * origin[n] - tmp.y * 0.0f;
			imag[i] += tmp.x * 0.0f      + tmp.y * origin[n];
		}
	}

	/* ���g������ */
	for (int i = 0; i < size; ++i)
	{
		//�U���X�y�N�g��
		float a = sqrtf(real[i] * real[i] + imag[i] * imag[i]);
		//�ʑ��X�y�N�g��
		float d = tanf(imag[i] / real[i]) / 2;

		printf("%f %f\n", a, d);
	}

	getchar();
}

// ���s
void Effector::Execution(const std::vector<float> & wave, std::vector<float> & adaptation, const unsigned int & index, const unsigned int & sample)
{
	DFT();

	param.attenuation = 0.5f;
	param.time = 0.375f;
	param.loop = 10;
	param.index = index;
	param.sample = sample;

	memcpy(info["b0"].data, &param, sizeof(Param));
	memcpy(info["u0"].data, &wave[0], sizeof(float) * wave.size());
	memset(info["u1"].data, 0, sizeof(float) * wave.size());

	list->Reset();

	list->GetList()->SetComputeRootSignature(root);
	list->GetList()->SetPipelineState(pipe);

	list->GetList()->SetDescriptorHeaps(1, &heap);

	auto size = dev.lock()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr = heap->GetGPUDescriptorHandleForHeapStart().ptr + size * info["b0"].index;
	list->GetList()->SetComputeRootDescriptorTable(0, handle);
	handle.ptr = heap->GetGPUDescriptorHandleForHeapStart().ptr + size * info["u0"].index;
	list->GetList()->SetComputeRootDescriptorTable(1, handle);
	handle.ptr = heap->GetGPUDescriptorHandleForHeapStart().ptr + size * info["u1"].index;
	list->GetList()->SetComputeRootDescriptorTable(2, handle);

	list->GetList()->Dispatch(static_cast<unsigned int>(wave.size()), 1, 1);

	list->GetList()->Close();

	ID3D12CommandList* com[] = {
		list->GetList(),
	};

	queue->Get()->ExecuteCommandLists(1, com);

	fence->Wait();

	adaptation.assign(info["u1"].data, info["u1"].data + wave.size());
}
