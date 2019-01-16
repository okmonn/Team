#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <vector>

namespace help {
	// �o�C�g�ϊ�
	int Byte(const int& i);

	// ���j�R�[�h�����ɕϊ�
	std::wstring ChangeWString(const std::string& st);

	// ������̌���
	bool CheckChar(const std::string& find, const unsigned char* data, const size_t& num);

	// �n�j���O���֐�
	float Haninng(const unsigned int& i, const size_t& size);

	// �V���N�֐�
	float Sinc(const float& i);

	// ���U�t�[���G�ϊ�
	void DFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag);

	// �t���U�t�[���G�ϊ�
	void IDFT(const std::vector<float>& real, const std::vector<float>& imag, std::vector<float>& out);

	// ���C���f�B�X�v���C�̉𑜓x�̎擾
	Vec2 GetDisplayResolution(void);

	// �L�[����
	int CheckKey(const int& key);

	// �S���̃L�[�����i�[
	void GetKeys(int* key);

	// �}�E�X���W�̎擾
	Vec2 GetMousePos(void);

	// �}�E�X���W�̃Z�b�g
	void SetMousePos(const Vec2& pos);
}
