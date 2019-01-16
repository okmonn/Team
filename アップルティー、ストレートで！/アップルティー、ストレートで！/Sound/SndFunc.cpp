#include "SndFunc.h"
#include "../Helper/Helper.h"
#include <algorithm>

// short�^�̃I�[�o�[�t���[�̖h�~
#define OVERFLLOW_SHORT 32768.0f

// char�^�̃I�[�o�[�t���[�̖h�~
#define OVERFLLOW_CHAR 127.0f

// �~����
#define PI 3.14159265f

// RIFF�̓ǂݍ���
int snd::LoadRIFF(RIFF & riff, FILE * file)
{
	if (file == nullptr)
	{
		return -1;
	}

	fread(&riff, sizeof(RIFF), 1, file);
	if (help::CheckChar("RIFF", riff.id, _countof(riff.id)) == false
		|| help::CheckChar("WAVE", riff.type, _countof(riff.type)) == false)
	{
		fclose(file);
		return -1;
	}

	return 0;
}

// FMT�̓ǂݍ���
int snd::LoadFMT(FMT & fmt, FILE * file)
{
	if (file == nullptr)
	{
		return -1;
	}

	fread(&fmt, sizeof(FMT), 1, file);
	if (help::CheckChar("fmt ", fmt.id, _countof(fmt.id)) == false)
	{
		fclose(file);
		return -1;
	}

	//�g�������̓ǂݍ���
	std::vector<unsigned char>extended(fmt.size - (sizeof(fmt) - sizeof(fmt.id) - sizeof(fmt.size)));
	if (extended.size() > 0)
	{
		fread(extended.data(), sizeof(unsigned char) * extended.size(), 1, file);
	}

	return 0;
}

// DATA�̓ǂݍ���
int snd::LoadDATA(DATA & data, FILE * file)
{
	if (file == nullptr)
	{
		return -1;
	}

	//�_�~�[�錾 
	std::string chunkID("1234");
	while (true)
	{
		fread(&chunkID[0], sizeof(unsigned char) * chunkID.size(), 1, file);

		//DATA�`�����N����
		if (chunkID == "data")
		{
			break;
		}
		//���̑��̃`�����N
		else
		{
			unsigned long size = 0;
			fread(&size, sizeof(size), 1, file);

			std::vector<unsigned char>data(size);
			fread(data.data(), sizeof(unsigned char) * data.size(), 1, file);
		}
	}

	//DATA�̓ǂݍ��� 
	data.id = chunkID;
	fread(&data.size, sizeof(data.size), 1, file);

	return 0;
}

// 8�r�b�g�g�`�̓ǂݍ���
void snd::LoadWave8(std::vector<float>& data, FILE * file)
{
	if (file == nullptr)
	{
		return;
	}
	std::vector<unsigned char>tmp(data.size());
	fread(tmp.data(), sizeof(unsigned char) * tmp.size(), 1, file);
	data.assign(tmp.begin(), tmp.end());
	std::for_each(data.begin(), data.end(), [&](float& i)->void {
		i /= OVERFLLOW_CHAR - 1.0f;
	});

	return;
}

// 16�r�b�g�g�`�̓ǂݍ���
void snd::LoadWave16(std::vector<float>& data, FILE * file)
{
	if (file == nullptr)
	{
		return;
	}
	std::vector<short>tmp(data.size());
	fread(tmp.data(), sizeof(short) * tmp.size(), 1, file);
	data.assign(tmp.begin(), tmp.end());
	std::for_each(data.begin(), data.end(), [&](float& i)->void {
		i /= OVERFLLOW_SHORT;
	});

	return;
}
