#pragma once
#include "SndFunc.h"
#include <functional>
#include <unordered_map>

class SndLoader
{
public:
	// �f�X�g���N�^
	~SndLoader();

	// �C���X�^���X�ϐ��̎擾
	static SndLoader& Get(void) {
		static SndLoader instance;
		return instance;
	}

	// �ǂݍ���
	int Load(const std::string& fileName);

	// �폜
	void Delete(const std::string& fileName);

	// �T�E���h���̎擾
	snd::Snd GetSnd(const std::string& fileName) {
		return sound[fileName];
	}

private:
	// �R���X�g���N�^
	SndLoader();
	SndLoader(const SndLoader&) = delete;
	void operator=(const SndLoader&) = delete;

	// �ǂݍ��݃e�[�u���̍쐬
	void Create(void);


	// �T�E���h���
	std::unordered_map<std::string, snd::Snd>sound;

	// �ǂݍ��݃e�[�u��
	std::unordered_map<int, std::function<void(std::vector<float>& tmp, FILE* file)>>load;
};
