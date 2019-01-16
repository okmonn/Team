#pragma once
#include <cmath>
#include <vector>

class Filter
{
public:
	// �R���X�g���N�^
	Filter();
	// �f�X�g���N�^
	~Filter();

	// ���[�p�X�t�B���^
	// cutoff���Ⴂ���g����ʂ�
	void LowPass(const float& cutoff, const float& sample, const float& q);

	// �n�C�p�X�t�B���^
	// cutoff��荂�����g����ʂ�
	void HighPass(const float& cutoff, const float& sample, const float& q);

	// �o���h�p�X�t�B���^
	// cutoff�𒆐S��wb���̎��g����ʂ�
	void BandPass(const float& cutoff, const float& sample, const float& bw);

	// �m�b�`�t�B���^
	// cutoff�𒆐S��wb���̎��g���ȊO��ʂ�
	void Notch(const float& cutoff, const float& sample, const float& bw = 1.0f);

	// ���[�V�F���t�t�B���^
	// cutoff���Ⴂ���g����gain��������������
	void Lowshelf(const float& cutoff, const float& gain, const float& sample, const float& q = 1.0f / std::sqrtf(2.0f));

	// �n�C�V�F���t�t�B���^
	// cutoff��荂�����g����gain��������������
	void Highshelf(const float& cutoff, const float& gain, const float& sample, const float& q = 1.0f / std::sqrtf(2.0f));

	// ���s
	void Execution(std::vector<float>& data);

private:
	// ���͒l�̕ێ�
	float input[2];

	// �o�͒l�̕ێ�
	float out[2];

	// �t�B���^�W��A
	float a[3];

	// �t�B���^�W��B
	float b[3];
};
