#pragma once
#include "TextureInfo.h"
#include <string>
#include <unordered_map>

class TexLoader
{
public:
	// �f�X�g���N�^
	~TexLoader();

	// �C���X�^���X�ϐ��̎擾
	static TexLoader& Get(void) {
		static TexLoader instance;
		return instance;
	}

	// �ǂݍ���
	long Load(const std::string& fileName);

	// �폜
	void Delete(const std::string& fileName);

	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(const std::string& fileName) {
		return info[fileName].rsc;
	}
	// �f�R�[�h�̎擾
	unsigned char* GetDecode(const std::string& fileName) {
		return info[fileName].decode.get();
	}
	// �T�u�f�[�^�̎擾
	std::shared_ptr<D3D12_SUBRESOURCE_DATA>GetSub(const std::string& fileName) {
		return info[fileName].sub;
	}
	// �摜�̉����̎擾
	unsigned int GetWidth(const std::string& fileName);
	// �摜�̉����̎擾
	unsigned int GetHeight(const std::string& fileName);

private:
	// �R���X�g���N�^
	TexLoader();
	TexLoader(const TexLoader&) = delete;
	void operator=(const TexLoader&) = delete;


	// ���f�[�^
	std::unordered_map<std::string, tex::Info>info;
};
