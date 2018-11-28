#include <d3dcompiler.h>
#include "Root.h"
#include "../Device/Device.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Root::Root(std::weak_ptr<Device> dev, const std::tstring & fileName) : 
	dev(dev), root(nullptr), sig(nullptr), error(nullptr), vertex(nullptr), pixel(nullptr)
{
	ShaderCompile(fileName);
	Create();
}

// �f�X�g���N�^
Root::~Root()
{
	Release(pixel);
	Release(vertex);
	Release(sig);
	Release(error);
	Release(root);
}

// �V�F�[�_�ǂݍ���
long Root::ShaderCompile(const std::tstring & fileName)
{
	auto hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "VS", "vs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex, &error);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���_�V�F�[�_�̓ǂݍ��݁F���s\n"));
		return hr;
	}

	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "PS", "ps_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel, &error);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�s�N�Z���V�F�[�_�̓ǂݍ��݁F���s\n"));
		return hr;
	}

	//�V�F�[�_���烋�[�g�V�O�l�`���̏����擾
	hr = D3DGetBlobPart(vertex->GetBufferPointer(), vertex->GetBufferSize(), D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���[�g�V�O�l�`�����̎擾�F���s\n"));
	}

	return hr;
}

// ���[�g�V�O�l�`���̐���
long Root::Create(void)
{
	auto hr = dev.lock()->Get()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���[�g�V�O�l�`���̐����F���s\n"));
	}

	return hr;
}
