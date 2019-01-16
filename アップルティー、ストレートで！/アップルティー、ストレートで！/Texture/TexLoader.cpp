#include "TexLoader.h"
#include "WICTextureLoader12.h"
#include "../Device/Device.h"
#include "../Helper/Helper.h"
#include "../etc/Release.h"

// �R���X�g���N�^
TexLoader::TexLoader()
{
	info.clear();
}

// �f�X�g���N�^
TexLoader::~TexLoader()
{
	for (auto itr = info.begin(); itr != info.end(); ++itr)
	{
		Release(itr->second.rsc);
		itr->second.decode.release();
	}
}

// �ǂݍ���
long TexLoader::Load(const std::string & fileName)
{
	if (info.find(fileName) != info.end())
	{
		OutputDebugString(_T("\n�ǂݍ��ݍς�\n"));
		return S_FALSE;
	}

	auto path = help::ChangeWString(fileName);
	info[fileName].sub = std::make_shared<D3D12_SUBRESOURCE_DATA>();

	auto hr = DirectX::LoadWICTextureFromFile(Device::Get().GetDev(), path.c_str(), &info[fileName].rsc, info[fileName].decode, *info[fileName].sub);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�e�N�X�`���̓ǂݍ��݁F���s\n"));
	}

	return hr;
}

// �폜
void TexLoader::Delete(const std::string & fileName)
{
	if (info.find(fileName) != info.end())
	{
		Release(info[fileName].rsc);
		info[fileName].decode.release();
		info.erase(info.find(fileName));
	}
}

// �摜�̉����̎擾
unsigned int TexLoader::GetWidth(const std::string & fileName)
{
	return static_cast<unsigned int>(info[fileName].rsc->GetDesc().Width);
}

// �摜�̉����̎擾
unsigned int TexLoader::GetHeight(const std::string & fileName)
{
	return static_cast<unsigned int>(info[fileName].rsc->GetDesc().Height);
}
