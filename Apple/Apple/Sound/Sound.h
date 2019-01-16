#pragma once
#include <string>
#include <vector>
#include <memory>
#include <thread>

struct IXAudio2SourceVoice;

class XAudio2;
class VoiceCallback;
class SoundLoader;
class Effector;
class Filter;

class Sound
{
public:
	// �R���X�g���N�^
	Sound();
	Sound(std::weak_ptr<Effector>effe);
	// �f�X�g���N�^
	~Sound();

	// �ǂݍ���
	void Load(const std::string& fileName);

	// �Đ�
	long Play(const bool& loop);

	// ��~
	long Stop(void);

	// �R�[���o�b�N�n���h���̎擾
	void* GetHandle(void) const;

	// ���[�p�X�t�B���^
	void LowPass(float& cutoff, const float& q = sqrtf(2.0f), const float& sample = 44100.0f);

	// �Đ��I���t���O�̎擾
	bool GetEnd(void) const {
		return end;
	}
	// �ǂݎ��z��ԍ��̎擾
	unsigned int GetRead(void) const {
		return read;
	}
	// �g�`���̎擾
	std::vector<float> GetWave(const unsigned int& i) {
		return wave[i];
	}

private:
	Sound(const Sound&) = delete;
	void operator=(const Sound&) = delete;

	// �\�[�X�{�C�X�̐���
	long CreateVoice(const std::string& filName);

	// �񓯊�����
	void Stream(void);


	// �G�t�F�N�^�[
	std::weak_ptr<Effector>effe;

	// �I�[�f�B�I
	XAudio2& audio;

	// ���[�_�[
	SoundLoader& loader;
	
	// �R�[���o�b�N
	std::unique_ptr<VoiceCallback>call;

	// �t�B���^�[
	std::unique_ptr<Filter>filter;

	// �\�[�X�{�C�X
	IXAudio2SourceVoice* voice;

	// ���[�v�t���O
	bool loop;

	// �Đ��I���t���O
	bool end;

	// �X���b�h�t���O
	bool threadFlag;

	// �ǂݎ��z��ԍ�
	unsigned int read;

	// �ǂݍ��݃t�@�C����
	std::string name;

	// �񓯊��X���b�h
	std::thread th;

	// �g�`�f�[�^
	std::vector<std::vector<float>>wave;
};
