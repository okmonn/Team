#include "Filter.h"
#include <algorithm>

// �~����
#define PI 3.14159265f

// �R���X�g���N�^
Filter::Filter()
{
	memset(input, 0, sizeof(a));
	memset(out,   0, sizeof(b));
	memset(a,     0, sizeof(a));
	memset(b,     0, sizeof(b));
	a[0] = 1.0f;
	b[0] = 1.0f;
}

// �f�X�g���N�^
Filter::~Filter()
{
}

// ���[�p�X�t�B���^
void Filter::LowPass(const float & cutoff, const float & sample, const float & q)
{
	float omega = 2.0f * PI * cutoff / sample;
	float alpha = std::sinf(omega) / (2.0f * q);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cosf(omega);
	a[2] =  1.0f - alpha;

	b[0] = (1.0f - std::cosf(omega)) / 2.0f;
	b[1] =  1.0f - std::cosf(omega);
	b[2] = (1.0f - std::cosf(omega)) / 2.0f;
}

// �n�C�p�X�t�B���^
void Filter::HighPass(const float & cutoff, const float & sample, const float & q)
{
	float omega = 2.0f * PI * cutoff / sample;
	float alpha = std::sinf(omega) / (2.0f * q);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cosf(omega);
	a[2] =  1.0f - alpha;

	b[0] =  (1.0f + std::cosf(omega)) / 2.0f;
	b[1] = -(1.0f + std::cosf(omega));
	b[2] =  (1.0f + std::cosf(omega)) / 2.0f;
}

// �o���h�p�X�t�B���^
void Filter::BandPass(const float & cutoff, const float & sample, const float & bw)
{
	float omega = 2.0f * PI * cutoff / sample;
	float alpha = std::sinf(omega) * std::sinhf(logf(2.0f) / 2.0f * bw * omega / std::sinf(omega));

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cosf(omega);
	a[2] =  1.0f - alpha;

	b[0] = alpha;
	b[1] = 0.0f;
	b[2] = -alpha;
}

// �m�b�`�t�B���^
void Filter::Notch(const float & cutoff, const float & sample, const float & bw)
{
	float omega = 2.0f * PI * cutoff / sample;
	float alpha = std::sinf(omega) * std::sinhf(logf(2.0f) / 2.0f * bw * omega / std::sinf(omega));

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cosf(omega);
	a[2] =  1.0f - alpha;

	b[0] =  1.0f;
	b[1] = -2.0f * std::cosf(omega);
	b[2] =  1.0f;
}

// ���[�V�F���t�t�B���^
void Filter::Lowshelf(const float & cutoff, const float & gain, const float & sample, const float & q)
{
	float omega = 2.0f * PI * cutoff / sample;
	float alpha = std::sinf(omega) / (2.0f * q);
	float delta = std::powf(10.0f, gain / 40.0f);
	float beta  = std::sqrtf(delta) / q;

	a[0] = (delta + 1.0f) + (delta - 1.0f) * std::cosf(omega) + beta * std::sinf(omega);
	a[1] = -2.0f * ((delta - 1.0f) + (delta + 1.0f) * std::cosf(omega));
	a[2] = (delta + 1.0f) + (delta - 1.0f) * std::cosf(omega) - beta * std::sinf(omega);

	b[0] = delta * ((delta + 1.0f) - (delta - 1.0f) * std::cosf(omega) + beta * std::sinf(omega));
	b[1] = 2.0f * delta * ((delta - 1.0f) - (delta + 1.0f) * std::cosf(omega));
	b[2] = delta * ((delta + 1.0f) - (delta - 1.0f) * std::cosf(omega) - beta * std::sinf(omega));
}

// �n�C�V�F���t�t�B���^
void Filter::Highshelf(const float & cutoff, const float & gain, const float & sample, const float & q)
{
	float omega = 2.0f * PI * cutoff / sample;
	float alpha = std::sinf(omega) / (2.0f * q);
	float delta = std::powf(10.0f, gain / 40.0f);
	float beta  = std::sqrtf(delta) / q;

	a[0] = (delta + 1.0f) - (delta - 1.0f) * std::cosf(omega) + beta * std::sinf(omega);
	a[1] =  2.0f * ((delta - 1.0f) - (delta + 1.0f) * std::cosf(omega));
	a[2] = (delta + 1.0f) - (delta - 1.0f) * std::cosf(omega) - beta * std::sinf(omega);

	b[0] = delta * ((delta + 1.0f) + (delta - 1.0f) * std::cosf(omega) + beta * std::sinf(omega));
	b[1] = -2.0f * delta * ((delta - 1.0f) + (delta + 1.0f) * std::cosf(omega));
	b[2] = delta * ((delta + 1.0f) + (delta - 1.0f) * std::cosf(omega) - beta * std::sinf(omega));
}

// ���s
void Filter::Execution(std::vector<float>& data)
{
	std::for_each(data.begin(), data.end(), [&](float& i)->void {
		float tmp = i;
		i = b[0] / a[0] * tmp + b[1] / a[0] * input[0] + b[2] / a[0] * input[1]
			- a[1] / a[0] * out[0] - a[2] / a[0] * out[1];

		input[1] = input[0];
		input[0] = tmp;

		out[1] = out[0];
		out[0] = i;
	});
}
