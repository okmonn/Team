#pragma once
#include <string>
#include <vector>

struct _iobuf;
typedef _iobuf FILE;

namespace sound
{
	// RIFF
	struct RIFF {
		unsigned char id[4];
		long size;
		unsigned char type[4];
	};

	// FMT
	struct FMT {
		unsigned char id[4];
		long size;
		short type;
		short channel;
		long sample;
		long byte;
		short block;
		short bit;
	};

	// DATA
	struct DATA {
		std::string id;
		long size;
	};

	// ������̊m�F
	bool CheckChar(const unsigned char* data, const std::string& find, const unsigned int& size);

	// RIFF�̓ǂݍ���
	int LoadRIFF(sound::RIFF& riff, FILE* file);

	// FMT�̓ǂݍ���
	int LoadFMT(sound::FMT& fmt, FILE* file);

	// DATA�̓ǂݍ���
	int LoadDATA(sound::DATA& data, FILE* file);

	// ���m�����E8�r�b�g
	void LoadMono8(std::vector<float>& data, FILE* file);

	// ���m�����E16�r�b�g
	void LoadMono16(std::vector<float>& data, FILE* file);

	// �X�e���I�E8�r�b�g
	void LoadStereo8(std::vector<float>& data, FILE* file);

	// �X�e���I�E16�r�b�g
	void LoadStereo16(std::vector<float>& data, FILE* file);
};
