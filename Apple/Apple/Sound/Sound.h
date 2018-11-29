#pragma once
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <unordered_map>

struct IXAudio2SourceVoice;

class XAudio2;
class VoiceCallback;
class SoundLoader;
class Effector;

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

	// �Đ��I���t���O�̎擾
	bool GetEnd(void) const {
		return end;
	}
	// �ǂݎ��z��ԍ��̎擾
	unsigned int GetRead(void) const {
		return read;
	}
	// �z��ԍ��̎擾
	unsigned int GetIndex(void) const {
		return index;
	}
	// �g�`�f�[�^�̎擾
	std::vector<float> GetWave(void) {
		return wave[index];
	}
	std::vector<float> GetWave(const unsigned int& i) {
		return wave[i];
	}

private:
	Sound(const Sound&);
	void operator=(const Sound&) {
	}


	// �\�[�X�{�C�X�̐���
	long CreateVoice(const std::string& filName);

	// �񓯊�����
	void Stream(void);


	// �I�[�f�B�I
	XAudio2& audio;

	// ���[�_�[
	SoundLoader& loader;

	// �G�t�F�N�^�[
	std::weak_ptr<Effector>effe;
	
	// �R�[���o�b�N
	std::unique_ptr<VoiceCallback>call;

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

	// �z��ԍ�
	unsigned int index;

	// �ǂݍ��݃t�@�C����
	std::string name;

	// �񓯊��X���b�h
	std::thread th;

	// �g�`�f�[�^
	std::vector<std::vector<float>>wave;
};
