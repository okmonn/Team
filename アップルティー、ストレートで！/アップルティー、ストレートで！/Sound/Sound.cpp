#include "Sound.h"
#include "Xaudio2.h"
#include "SndLoader.h"
#include "VoiceCallback.h"
#include "Filter.h"
#include "../Helper/Helper.h"
#include <ks.h>
#include <ksmedia.h>
#include <tchar.h>

// �o�b�t�@��
#define BUFFER 2

// �I�t�Z�b�g
#define OFFSET 10

// �X�s�[�J�[�ݒ�p�z��
const unsigned long spk[] = {
	KSAUDIO_SPEAKER_MONO,
	KSAUDIO_SPEAKER_STEREO,
	KSAUDIO_SPEAKER_STEREO | SPEAKER_LOW_FREQUENCY,
	KSAUDIO_SPEAKER_QUAD,
	0,
	KSAUDIO_SPEAKER_5POINT1,
	0,
	KSAUDIO_SPEAKER_7POINT1_SURROUND
};

// �R���X�g���N�^
Sound::Sound() : 
	voice(nullptr), loop(false), flag(true), read(0)
{
	call   = std::make_unique<VoiceCallback>();
	filter = std::make_unique<Filter>();
	state  = std::make_unique<XAUDIO2_VOICE_STATE>();

	data.resize(BUFFER);
}

// �R���X�g���N�^
Sound::Sound(const std::string & fileName) :
	voice(nullptr), loop(false), flag(true), read(0)
{
	call   = std::make_unique<VoiceCallback>();
	filter = std::make_unique<Filter>();
	state  = std::make_unique<XAUDIO2_VOICE_STATE>();

	data.resize(BUFFER);

	Load(fileName);
}

// �R���X�g���N�^
Sound::Sound(const snd::Info & info) :
	voice(nullptr), loop(false), flag(true), read(0)
{
	call   = std::make_unique<VoiceCallback>();
	filter = std::make_unique<Filter>();
	state  = std::make_unique<XAUDIO2_VOICE_STATE>();
	
	data.resize(BUFFER);

	CopyInfo(info);
}

// �f�X�g���N�^
Sound::~Sound()
{
	flag = false;
	if (th.joinable() == true)
	{
		th.join();
	}

	if (voice != nullptr)
	{
		voice->DestroyVoice();
	}
}

// �\�[�X�{�C�X�̐���
long Sound::CreateVoice(void)
{
	WAVEFORMATEXTENSIBLE desc{};
	desc.Format.cbSize          = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
	desc.Format.nChannels       = SndLoader::Get().GetSnd(name).channel;
	desc.Format.nSamplesPerSec  = SndLoader::Get().GetSnd(name).sample;
	desc.Format.nBlockAlign     = sizeof(float) * desc.Format.nChannels;
	desc.Format.wBitsPerSample  = sizeof(float) * 8;
	desc.Format.nAvgBytesPerSec = desc.Format.nSamplesPerSec * desc.Format.nBlockAlign;
	desc.Format.wFormatTag      = WAVE_FORMAT_EXTENSIBLE;

	desc.dwChannelMask               = spk[desc.Format.nChannels - 1];
	desc.Samples.wValidBitsPerSample = desc.Format.wBitsPerSample;
	desc.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

	auto hr = Xaudio2::Get().GetAudio()->CreateSourceVoice(&voice, (WAVEFORMATEX*)(&desc), 0, 1.0f, &(*call));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�\�[�X�{�C�X�̐����F���s\n"));
	}

	return hr;
}

// �\�[�X�{�C�X�̐���
long Sound::CreateVoice(const snd::Info & info)
{
	WAVEFORMATEXTENSIBLE desc{};
	desc.Format.cbSize          = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
	desc.Format.nChannels       = info.channel;
	desc.Format.nSamplesPerSec  = info.sample;
	desc.Format.nBlockAlign     = sizeof(float) * desc.Format.nChannels;
	desc.Format.wBitsPerSample  = sizeof(float) * 8;
	desc.Format.nAvgBytesPerSec = desc.Format.nSamplesPerSec * desc.Format.nBlockAlign;
	desc.Format.wFormatTag      = WAVE_FORMAT_EXTENSIBLE;

	desc.dwChannelMask               = spk[desc.Format.nChannels - 1];
	desc.Samples.wValidBitsPerSample = desc.Format.wBitsPerSample;
	desc.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

	auto hr = Xaudio2::Get().GetAudio()->CreateSourceVoice(&voice, (WAVEFORMATEX*)(&desc), 0, 1.0f, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�\�[�X�{�C�X�̐����F���s\n"));
	}

	return hr;
}

// �ǂݍ���
void Sound::Load(const std::string & fileName)
{
	if (th.joinable() == true)
	{
		return;
	}

	SndLoader::Get().Load(fileName);

	name = fileName;
	CreateVoice();

	th = std::thread(&Sound::StreamFile, this);
}

// �T�E���h��񂩂�T�E���h�̐���
void Sound::CopyInfo(const snd::Info & info)
{
	CreateVoice(info);

	for (auto& i : data)
	{
		i = info.data;
	}
	
	th = std::thread(&Sound::StreamInfo, this);
}

// ���[�p�X�t�B���^
void Sound::LowPass(const float & cutoff, const float & sample, const float & q)
{
	filter->LowPass(cutoff, sample, q);
}

// �n�C�p�X�t�B���^
void Sound::HightPass(const float & cutoff, const float & sample, const float & q)
{
	filter->HighPass(cutoff, sample, q);
}

// �o���h�p�X�t�B���^
void Sound::BandPass(const float & cutoff, const float & sample, const float & bw)
{
	filter->BandPass(cutoff, sample, bw);
}

// �Đ�
long Sound::Play(const bool& loop)
{
	auto hr = voice->Start();
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�Đ��F���s\n"));
		return hr;
	}

	this->loop = loop;
	return hr;
}

// ��~
long Sound::Stop(void)
{
	WaitForSingleObject(call->handle, INFINITE);

	auto hr = voice->Stop();
	if (FAILED(hr))
	{
		OutputDebugString(_T("��~�F���s\n"));
	}

	return hr;
}

// �Đ��|�C���g�̃��Z�b�g
void Sound::Reset(void)
{
	state->BuffersQueued = 0;
	read = 0;
}

// �t�@�C������̔񓯊�����
void Sound::StreamFile(void)
{
	unsigned int index = 0;
	unsigned int size  = 0;
	while (flag)
	{
		voice->GetState(&(*state));
		if (state->BuffersQueued >= BUFFER)
		{
			continue;
		}

		size = (SndLoader::Get().GetSnd(name).data->size() - read > static_cast<unsigned int>(SndLoader::Get().GetSnd(name).sample / OFFSET)) ? 
			SndLoader::Get().GetSnd(name).sample / OFFSET : SndLoader::Get().GetSnd(name).data->size() - read;
		data[index].assign(&SndLoader::Get().GetSnd(name).data->at(read), &SndLoader::Get().GetSnd(name).data->at(read + size));

		XAUDIO2_BUFFER buf{};
		buf.AudioBytes = static_cast<unsigned int>(sizeof(float) * data[index].size());
		buf.pAudioData = (unsigned char*)(data[index].data());
		auto hr = voice->SubmitSourceBuffer(&buf);
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n�T�E���h�����o�b�t�@�ɒǉ��F���s\n"));
			continue;
		}

		index = (index + 1 >= BUFFER) ? 0 : ++index;
		read += size;
		if (read >= SndLoader::Get().GetSnd(name).data->size() / help::Byte(SndLoader::Get().GetSnd(name).bit))
		{
			if (loop == false)
			{
				Stop();
				index = 0;
				read  = 0;
			}
		}
	}
}

// �T�E���h��񂩂�̔񓯊�����
void Sound::StreamInfo(void)
{
	unsigned int index = 0;
	while (flag)
	{
		voice->GetState(&(*state));
		if (state->BuffersQueued >= BUFFER)
		{
			continue;
		}

		filter->Execution(data[index]);

		XAUDIO2_BUFFER buf{};
		buf.AudioBytes = sizeof(float) * static_cast<unsigned int>(data[index].size());
		buf.pAudioData = (unsigned char*)data[index].data();
		auto hr = voice->SubmitSourceBuffer(&buf);
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n�o�b�t�@�̒ǉ��F���s\n"));
			continue;
		}

		index = (index + 1 >= BUFFER) ? 0 : ++index;
		if (loop == false)
		{
			Stop();
			index = 0;
		}
	}
}

