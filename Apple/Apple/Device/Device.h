#pragma once

struct ID3D12Device;

class Device
{
public:
	// �R���X�g���N�^
	Device();
	// �f�X�g���N�^
	~Device();

	// �f�o�C�X�̎擾
	ID3D12Device* Get(void) const {
		return dev;
	}

private:
	// �f�o�C�X�̐���
	long CreateDev(void);


	// �f�o�C�X
	ID3D12Device* dev;
};
