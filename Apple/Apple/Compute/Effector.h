#pragma once
#include "Compute.h"
#include "../etc/tString.h"
#include <vector>

class Effector :
	public Compute
{
	// �p�����[�^
	struct Param {
		//�T���v�����O���g��
		float sample;
		//������
		float gain;
		//���ʃ��x��
		float volume;
		//�ϒ��[�x
		float depth;
		//�ϒ����g��
		float rate;
	};

public:
	// �R���X�g���N�^
	Effector(std::weak_ptr<Device>dev, const std::tstring& fileName);
	// �f�X�g���N�^
	~Effector();

	// ������
	void Init(const unsigned int& num);

	// ���s
	void Execution(const std::vector<float>& input, std::vector<float>& out);

	// �T���v�����O���g���̃Z�b�g
	void SetSample(const float& sample);

	// �������̃Z�b�g
	void SetGain(const float& gain);

	// �{�����[���̃Z�b�g
	void SetVolume(const float& volume);

	// �ϒ��[�x�̃Z�b�g
	void SetDepth(const float& depth);

	// �ϒ����g���̃Z�b�g
	void SetRate(const float& rate);

private:
	// �p�����[�^
	Param param;
};
