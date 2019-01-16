#pragma once
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <unordered_map>

class SoundLoader
{
	//�T�E���h���
	struct Wave {
		//�t�@�C���n���h��
		FILE* file;
		//�`�����l����
		int channel;
		//�T���v�����O���g��
		int sample;
		//�ʎq���r�b�g��
		int bit;
		//�g�`���
		std::vector<std::vector<float>>data;
	};

public:
	// �f�X�g���N�^
	~SoundLoader();

	// �C���X�^���X�ϐ��̎擾
	static SoundLoader& Get(void) {
		static SoundLoader instance;
		return instance;
	}

	// �ǂݍ���
	int Load(const std::string& fileName);

	// �`�����l�����̎擾
	int GetChannel(const std::string& fileName) {
		return wave[fileName].channel;
	}
	// �T���v�����O���g���̎擾
	int GetSample(const std::string& fileName) {
		return wave[fileName].sample;
	}
	// �ʎq���r�b�g���̎擾
	int GetBit(const std::string& fileName) {
		return wave[fileName].bit;
	}
	// �g�`���̎擾
	std::vector<std::vector<float>>& GetWave(const std::string& fileName) {
		return wave[fileName].data;
	}

private:
	// �R���X�g���N�^
	SoundLoader();
	SoundLoader(const SoundLoader&) = delete;
	void operator=(const SoundLoader&) = delete;

	// �ǂݍ��݃e�[�u���̐���
	void InitLoadTbl(void);

	// �񓯊��ǂݍ���
	void Stream(const std::string& fileName);


	// �X���b�h�I���t���O
	bool threadFlag;

	// �X���b�h
	std::vector<std::thread>th;

	// �T�E���h���
	std::unordered_map<std::string, Wave>wave;

	// �ǂݍ��݃e�[�u��
	std::unordered_map<int, std::unordered_map<int, std::function<void(std::vector<float>& tmp, FILE* file)>>>load;
};
