#include "SoundMane.h"
#include "../Sound/Sound.h"

// �R���X�g���N�^
SoundMane::SoundMane()
{
	sound.clear();
}

// �f�X�g���N�^
SoundMane::~SoundMane()
{
	sound.clear();
}

// �T�E���h�̓ǂݍ���
void SoundMane::Load(const std::string & name, const std::string & fileName)
{
	if (sound.find(name) != sound.end())
	{
		return;
	}

	sound[name] = std::make_unique<Sound>();
	sound[name]->Load(fileName);
}

// �T�E���h�̍Đ�
void SoundMane::Play(const std::string & name, const bool & loop)
{
	if (sound.find(name) == sound.end())
	{
		return;
	}
	sound[name]->Play(loop);
}

// �T�E���h�̒�~
void SoundMane::Stop(const std::string & name)
{
	if (sound.find(name) == sound.end())
	{
		return;
	}
	sound[name]->Stop();
}
