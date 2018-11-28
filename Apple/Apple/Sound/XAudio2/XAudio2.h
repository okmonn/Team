#pragma once

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio2
{
public:
	// �f�X�g���N�^
	~XAudio2();

	// �C���X�^���X�ϐ��̎擾
	static XAudio2& Get(void) {
		static XAudio2 instance;
		return instance;
	}

	// �I�[�f�B�I�̎擾
	IXAudio2* GetAudio(void) const {
		return audio;
	}
	// �}�X�^�����O�̎擾
	IXAudio2MasteringVoice* GetMastering(void) const {
		return mastering;
	}

private:
	// �R���X�g���N�^
	XAudio2();
	XAudio2(const XAudio2&) {
	}
	void operator=(const XAudio2&) {
	}

	// COM�̏�����
	long InitCom(void);

	// �I�[�f�B�I�̐���
	long CreateAudio(void);

	// �}�X�^�����O�̐���
	long CreateMastering(void);

	// ������
	void Init(void);


	// �I�[�f�B�I
	IXAudio2* audio;

	// �}�X�^�����O
	IXAudio2MasteringVoice* mastering;
};
