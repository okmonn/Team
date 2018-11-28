#include "SoundFunc.h"

// short�^�̃I�[�o�[�t���[�̖h�~
#define OVERFLLOW_SHORT 32768.0f

// char�^�̃I�[�o�[�t���[�̖h�~
#define OVERFLLOW_CHAR 127.0f

// �X�e���I8�r�b�g
struct Stereo8 {
	unsigned char left;
	unsigned char right;

	void operator=(const int& i) {
		left = i;
		right = i;
	}
};

// �X�e���I16�r�b�g
struct Stereo16 {
	short left;
	short right;

	void operator=(const int& i) {
		left = i;
		right = i;
	}
};

// ������̊m�F
bool sound::CheckChar(const unsigned char * data, const std::string & find, const unsigned int & size)
{
	unsigned int index = 0;
	for (unsigned int i = 0; i < size; ++i)
	{
		if (data[i] == find[index])
		{
			if (index + 1 >= find.size())
			{
				return true;
			}

			++index;
		}
	}

	return false;
}

// RIFF�̓ǂݍ���
int sound::LoadRIFF(sound::RIFF & riff, FILE * file)
{
	fread(&riff, sizeof(RIFF), 1, file);
	if (CheckChar(riff.id, "RIFF", _countof(riff.id)) == false
		|| CheckChar(riff.type, "WAVE", _countof(riff.type)) == false)
	{
		fclose(file);
		return -1;
	}

	return 0;
}

// FMT�̓ǂݍ���
int sound::LoadFMT(sound::FMT & fmt, FILE * file)
{
	fread(&fmt, sizeof(FMT), 1, file);
	if (CheckChar(fmt.id, "fmt ",_countof(fmt.id)) == false)
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
int sound::LoadDATA(sound::DATA & data, FILE * file)
{
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

// ���m�����E8�r�b�g
void sound::LoadMono8(std::vector<float>& data, FILE * file)
{
	unsigned char tmp = 0;
	for (auto& i : data)
	{
		if (feof(file) == 0)
		{
			fread(&tmp, sizeof(unsigned char), 1, file);
		}
		else
		{
			tmp = 0;
		}

		//float�l�ɕϊ��E���f�[�^��-1�`1�͈̔͂ɐ��K��
		i = static_cast<float>(tmp) / OVERFLLOW_CHAR - 1.0f;
	}
}

// ���m�����E16�r�b�g
void sound::LoadMono16(std::vector<float>& data, FILE * file)
{
	short tmp = 0;
	for (auto& i : data)
	{
		if (feof(file) == 0)
		{
			fread(&tmp, sizeof(short), 1, file);
		}
		else
		{
			tmp = 0;
		}

		//float�l�ɕϊ��E���f�[�^��-1�`1�͈̔͂ɐ��K��
		i = static_cast<float>(tmp) / OVERFLLOW_SHORT;
	}
}

// �X�e���I�E8�r�b�g
void sound::LoadStereo8(std::vector<float>& data, FILE * file)
{
	Stereo8 tmp{};
	for (unsigned int i = 0; i < data.size(); i += 2)
	{
		if (feof(file) == 0)
		{
			fread(&tmp, sizeof(Stereo8), 1, file);
		}
		else
		{
			tmp = 0;
		}

		//float�l�ɕϊ��E���f�[�^��-1�`1�͈̔͂ɐ��K��
		data[i] = static_cast<float>(tmp.left) / OVERFLLOW_CHAR - 1.0f;
		data[i + 1] = static_cast<float>(tmp.right) / OVERFLLOW_CHAR - 1.0f;
	}
}

// �X�e���I�E16�r�b�g
void sound::LoadStereo16(std::vector<float>& data, FILE * file)
{
	Stereo16 tmp{};
	for (unsigned int i = 0; i < data.size(); i += 2)
	{
		if (feof(file) == 0)
		{
			fread(&tmp, sizeof(Stereo16), 1, file);
		}
		else
		{
			tmp = 0;
		}

		//float�l�ɕϊ�
		data[i] = static_cast<float>(tmp.left) / OVERFLLOW_SHORT;
		data[i + 1] = static_cast<float>(tmp.right) / OVERFLLOW_SHORT;
	}
}
