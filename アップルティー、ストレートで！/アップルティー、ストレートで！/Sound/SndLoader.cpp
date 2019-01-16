#include "SndLoader.h"
#include "../Helper/Helper.h"
#include <Windows.h>
#include <tchar.h>

// �R���X�g���N�^
SndLoader::SndLoader()
{
	sound.clear();

	Create();
}

// �f�X�g���N�^
SndLoader::~SndLoader()
{
}

// �ǂݍ��݃e�[�u���̍쐬
void SndLoader::Create(void)
{
	load[8] = [&](std::vector<float>& tmp, FILE* file)->void {
		snd::LoadWave8(tmp, file);
	};

	load[16] = [&](std::vector<float>& tmp, FILE* file)->void {
		snd::LoadWave16(tmp, file);
	};
}

// �ǂݍ���
int SndLoader::Load(const std::string & fileName)
{
	if (sound.find(fileName) != sound.end())
	{
		OutputDebugString(_T("\n�ǂݍ��ݍς�\n"));
		return -1;
	}

	if (fopen_s(&sound[fileName].file, fileName.c_str(), "rb") != 0)
	{
		OutputDebugString(_T("\n�t�@�C���̎Q�ƁF���s\n"));
		return -1;
	}

	snd::RIFF riff{};
	snd::FMT fmt{};
	snd::DATA data{};

	snd::LoadRIFF(riff, sound[fileName].file);
	snd::LoadFMT(fmt, sound[fileName].file);
	snd::LoadDATA(data, sound[fileName].file);

	//���l�̊i�[
	sound[fileName].channel = fmt.channel;
	sound[fileName].sample  = fmt.sample;
	sound[fileName].bit     = fmt.bit;
	sound[fileName].length  = data.size / fmt.byte;

	sound[fileName].data = std::make_shared<std::vector<float>>(data.size / help::Byte(fmt.bit));

	load[sound[fileName].bit](*sound[fileName].data, sound[fileName].file);

	return 0;
}

// �폜
void SndLoader::Delete(const std::string & fileName)
{
	if (sound.find(fileName) != sound.end())
	{
		sound.erase(sound.find(fileName));
	}
}
