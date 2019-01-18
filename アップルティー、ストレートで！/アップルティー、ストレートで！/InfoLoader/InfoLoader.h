#pragma once
#include "../Typedef.h"
#include <memory>
#include <unordered_map>

class InfoLoader
{
public:
	// �f�X�g���N�^
	~InfoLoader();

	// �C���X�^���X�ϐ��̎擾
	static InfoLoader& Get(void) {
		static InfoLoader instance;
		return instance;
	}

	// �ǂݍ���
	int Load(const std::string& fileName);

	// ��������
	int Write(const std::string& fileName, const std::vector<Info>& info);

	// ���̎擾
	std::shared_ptr<std::unordered_map<std::string, Info>> GetInfo(const std::string& fileName) {
		return info[fileName];
	}

private:
	// �R���X�g���N�^
	InfoLoader();
	InfoLoader(const InfoLoader&) = delete;
	void operator=(const InfoLoader&) = delete;


	// ���
	std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, Info>>>info;
};
