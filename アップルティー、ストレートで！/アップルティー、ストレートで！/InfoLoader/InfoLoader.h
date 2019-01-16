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

	// �A�j���[�V�����E��`���̏�������
	int WriteInfo(const std::string& fileName, const std::vector<Info>& info);

	// �A�j���[�V�������Ԃ̎擾
	std::shared_ptr<std::unordered_map<std::string, float>> GetAnimTime(const std::string& fileName) {
		return animTime[fileName];
	}
	// �A�j���[�V�����E��`���̎擾
	std::shared_ptr<std::unordered_map<std::string, std::vector<Rect>>> GetRect(const std::string& fileName) {
		return rect[fileName];
	}

private:
	// �R���X�g���N�^
	InfoLoader();
	InfoLoader(const InfoLoader&) = delete;
	void operator=(const InfoLoader&) = delete;


	// �A�j���[�V��������
	std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, float>>>animTime;

	// �A�j���[�V�����E��`���
	std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::vector<Rect>>>>rect;
};
