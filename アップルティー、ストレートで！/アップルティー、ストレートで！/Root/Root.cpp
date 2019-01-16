#include <d3dcompiler.h>
#include "Root.h"
#include "../Device/Device.h"
#include "../etc/Release.h"

#pragma comment(lib, "d3dcompiler.lib")

// �R���X�g���N�^
Root::Root(const std::wstring& fileName) : 
	root(nullptr), sig(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
	CompileShader(fileName);
	GetRootInfo();
	Create();
}

// �f�X�g���N�^
Root::~Root()
{
	Release(compute);
	Release(pixel);
	Release(geometry);
	Release(vertex);
	Release(sig);
	Release(root);
}

// �V�F�[�_�̃R���p�C��
long Root::CompileShader(const std::wstring & fileName)
{
	auto hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex, nullptr);
	if (FAILED(hr))
	{
		hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "CS", "cs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &compute, nullptr);
		if (hr == S_OK)
		{
			OutputDebugString(_T("\n�R���s���[�g�V�F�[�_�̓ǂݍ��݁F����\n"));
			return hr;
		}
		OutputDebugString(_T("\n���_�V�F�[�_�̓ǂݍ��݁F���s\n"));
		return hr;
	}

	hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS", "gs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &geometry, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�W�I���g���V�F�[�_�̓ǂݍ��݁F���s\n"));
		OutputDebugString(_T("�W�I���g���V�F�[�_���g�p���Ă��Ȃ��ꍇ�͖�������OK\n"));
	}

	hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�s�N�Z���V�F�[�_�̓ǂݍ��݁F���s\n"));
		return hr;
	}

	return hr;
}

// ���[�g�V�O�l�`�����̎擾
long Root::GetRootInfo(void)
{
	auto hr = S_OK;
	if (vertex != nullptr)
	{
		hr = D3DGetBlobPart(vertex->GetBufferPointer(), vertex->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n���[�g�V�O�l�`�����̎擾�F���s\n"));
		}
	}
	else
	{
		hr = D3DGetBlobPart(compute->GetBufferPointer(), compute->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n���[�g�V�O�l�`�����̎擾�F���s\n"));
		}
	}

	return hr;
}

// ���[�g�V�O�l�`���̐���
long Root::Create(void)
{
	auto hr = Device::Get().GetDev()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���[�g�V�O�l�`���̐����F���s\n"));
	}

	return hr;
}
