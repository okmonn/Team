#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Effector;
class Sound;

class SoundMane
{
public:
	// �f�X�g���N�^
	~SoundMane();

	// �C���X�^���X�ϐ��̎擾
	static SoundMane& Get(void) {
		static SoundMane instance;
		return instance;
	}

	// �T�E���h�̓ǂݍ���
	void Load(const std::string& name, const std::string& fileName);

	// �T�E���h�̍Đ�
	void Play(const std::string& name, const bool& loop = false);

	// �T�E���h�̒�~
	void Stop(const std::string& name);

private:
	// �R���X�g���N�^
	SoundMane();
	SoundMane(const SoundMane&) = delete;
	void operator=(const SoundMane&) = delete;


	// �T�E���h
	std::unordered_map<std::string, std::unique_ptr<Sound>>sound;
};
