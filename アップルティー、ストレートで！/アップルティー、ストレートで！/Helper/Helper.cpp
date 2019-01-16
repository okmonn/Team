#include "Helper.h"
#include <Windows.h>

// �~����
#define PI 3.14159265f

// �o�C�g�ϊ�
int help::Byte(const int & i)
{
	return i / 8;
}

// ���j�R�[�h�����ɕϊ�
std::wstring help::ChangeWString(const std::string & st)
{
	//�������̎擾
	auto byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, st.c_str(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.resize(byteSize);

	//�ϊ�
	byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, st.c_str(), -1, &wstr[0], byteSize);

	return wstr;
}

// ������̌���
bool help::CheckChar(const std::string & find, const unsigned char * data, const size_t & num)
{
	unsigned int index = 0;
	for (size_t i = 0; i < num; ++i)
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

// �n�j���O���֐�
float help::Haninng(const unsigned int & i, const size_t & size)
{
	float tmp = 0.0f;

	tmp = (size % 2 == 0) ?
		//����
		0.5f - 0.5f * std::cosf(2.0f * PI * i / size) :
		//�
		0.5f - 0.5f * std::cosf(2.0f * PI * (i + 0.5f) / size);

	if (tmp == 0.0f)
	{
		tmp = 1.0f;
	}

	return tmp;
}

// �V���N�֐�
float help::Sinc(const float & i)
{
	return (i == 0.0f) ? 1.0f : std::sinf(i) / i;
}

// ���U�t�[���G��
void help::DFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag)
{
	real = input;
	imag.assign(input.size(), 0.0f);

	float tmpR = 0.0f;
	float tmpI = 0.0f;
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		for (unsigned int n = 0; n < input.size(); ++n)
		{
			tmpR =  std::cosf(2.0f * PI * i * n / input.size());
			tmpI = -std::sinf(2.0f * PI * i * n / input.size());

			real[i] += tmpR * (input[n] * Haninng(n, input.size())) - tmpI * 0.0f;
			imag[i] += tmpR * 0.0f                                  + tmpI * (input[n] * Haninng(n, input.size()));
		}
	}
}

// �t���U�t�[���G�ϊ�
void help::IDFT(const std::vector<float>& real, const std::vector<float>& imag, std::vector<float>& out)
{
	out.assign(real.size(), 0.0f);

	float tmpR = 0.0f;
	float tmpI = 0.0f;
	for (unsigned int i = 0; i < real.size(); ++i)
	{
		float tmp = 0.0f;
		for (unsigned int n = 0; n < real.size(); ++i)
		{
			tmpR = std::cosf(2.0f * PI * i * n / real.size());
			tmpI = std::sinf(2.0f * PI * i * n / real.size());

			out[i] += (tmpR * real[n] - tmpI * imag[n]) / real.size();
			tmp    += (tmpR * imag[n] + tmpI * real[n]) / real.size();
		}

		out[i] /= Haninng(i, real.size());
		tmp    /= Haninng(i, real.size());
	}
}

// ���C���f�B�X�v���C�̉𑜓x�̎擾
Vec2 help::GetDisplayResolution(void)
{
	return Vec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

// �L�[����
int help::CheckKey(const int & key)
{
	return (GetKeyState(key) & 0x80);
}

// �S���̃L�[�����i�[
void help::GetKeys(int * key)
{
	SetKeyboardState((unsigned char*)key);
}

// �}�E�X���W�̎擾
Vec2 help::GetMousePos(void)
{
	POINT point;
	GetCursorPos(&point);
	return { static_cast<int>(point.x), static_cast<int>(point.y) };
}

// �}�E�X���W�̃Z�b�g
void help::SetMousePos(const Vec2 & pos)
{
	SetCursorPos(pos.x, pos.y);
}
