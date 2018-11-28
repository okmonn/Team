#pragma once
#include <map>
#include <string>
#include <memory>

struct D3D12_SUBRESOURCE_DATA;
struct ID3D12Resource;
class Device;

class TextureLoad
{
	// ���f�[�^
	struct Origin {
		//���\�[�X
		ID3D12Resource* rsc;
		//�f�R�[�h
		std::unique_ptr<unsigned char[]>decode;
		//�T�u�f�[�^
		std::shared_ptr<D3D12_SUBRESOURCE_DATA>sub;
	};

public:
	// �f�X�g���N�^
	~TextureLoad();

	// �C���X�^���X�ϐ��̎擾
	static TextureLoad& Get(void) {
		static TextureLoad instance;
		return instance;
	}

	// �ǂݍ���
	long Load(std::weak_ptr<Device>dev, const std::string& fileName);

	// �摜�̉����̎擾
	unsigned int GetWidth(const std::string& fileName);

	// �摜�̉����̎擾
	unsigned int GetHeight(const std::string& fileName);

	// �f�[�^�̍폜
	void Delete(const std::string& fileName);

	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(const std::string& fileName) {
		return origin[fileName].rsc;
	}
	// �f�R�[�h�̎擾
	unsigned char* GetDecode(const std::string& fileName) {
		return origin[fileName].decode.get();
	}
	// �T�u�f�[�^�̎擾
	std::shared_ptr<D3D12_SUBRESOURCE_DATA>GetSub(const std::string& fileName) {
		return origin[fileName].sub;
	}

private:
	// �R���X�g���N�^
	TextureLoad();
	TextureLoad(const TextureLoad&) {
	}
	void operator=(const TextureLoad&) {
	}

	// �I���W���f�[�^
	std::map<std::string, Origin>origin;
};
